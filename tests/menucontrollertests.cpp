#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/menucontroller.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/controlplane.hpp"
#include "../app/gameplayview.hpp"
#include <QWidget>
#include <QSignalSpy>

class MenuControllerTest : public MenuController
{
public:
    MenuControllerTest(QWidget*            displayWidget,
                       ControlPlane*       controller,
                       GameplayView*       gameplayView,
                       AnimationPlaneView* animationView)
                        : MenuController(displayWidget,
                                         controller,
                                         gameplayView,
                                         animationView) {}
    virtual ~MenuControllerTest() {}
};

class MenuControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(MenuControllerTestsClass, PauseGame_CheckCorrectWorking_ShouldSendGamePauseSignal)
{
    QWidget            displayWidget;
    ControlPlane       controller(&displayWidget);
    GameplayView       gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    MenuControllerTest menuController(&displayWidget,
                                      &controller,
                                      &gameplayView,
                                      &animationView);
    QSignalSpy signalGamePaused(&menuController, &MenuControllerTest::gamePaused);
    signalGamePaused.wait(utdef::minSignalTimeDelay);

    menuController.pauseGame();
    int resultSignalGamePaused = signalGamePaused.count();

    EXPECT_EQ(1, resultSignalGamePaused);
}
