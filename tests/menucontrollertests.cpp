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

    bool getIsGameStarted() const { return m_isGameStarted; }
    bool getIsGamePaused()  const { return m_isGamePaused; }
    void setIsGameStarted(bool value) { m_isGameStarted = value; }
    void setIsGamePaused(bool value)  { m_isGamePaused  = value; }
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

TEST_F(MenuControllerTestsClass, PauseGame_GameNotStarted_ShouldDoNothing)
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
    int  resultSignalGamePaused = signalGamePaused.count();
    bool resultIsGamePaused     = menuController.getIsGamePaused();

    EXPECT_EQ(0, resultSignalGamePaused);
    EXPECT_FALSE(resultIsGamePaused);
}

TEST_F(MenuControllerTestsClass, PauseGame_GameStartedAndNotPaused_ShouldSendSignalGamePausedAndSetIsGamePausedAsTrue)
{
    QWidget            displayWidget;
    ControlPlane       controller(&displayWidget);
    GameplayView       gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    MenuControllerTest menuController(&displayWidget,
                                      &controller,
                                      &gameplayView,
                                      &animationView);
    menuController.setIsGameStarted(true);
    QSignalSpy signalGamePaused(&menuController, &MenuControllerTest::gamePaused);
    signalGamePaused.wait(utdef::minSignalTimeDelay);

    menuController.pauseGame();
    int  resultSignalGamePaused = signalGamePaused.count();
    bool resultIsGamePaused     = menuController.getIsGamePaused();

    EXPECT_EQ(1, resultSignalGamePaused);
    EXPECT_TRUE(resultIsGamePaused);
}

TEST_F(MenuControllerTestsClass, PauseGame_GameStartedAndPaused_ShouldDoNothing)
{
    QWidget            displayWidget;
    ControlPlane       controller(&displayWidget);
    GameplayView       gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    MenuControllerTest menuController(&displayWidget,
                                      &controller,
                                      &gameplayView,
                                      &animationView);
    menuController.setIsGameStarted(true);
    menuController.setIsGamePaused(true);
    QSignalSpy signalGamePaused(&menuController, &MenuControllerTest::gamePaused);
    signalGamePaused.wait(utdef::minSignalTimeDelay);

    menuController.pauseGame();
    int  resultSignalGamePaused = signalGamePaused.count();
    bool resultIsGamePaused     = menuController.getIsGamePaused();

    EXPECT_EQ(0, resultSignalGamePaused);
    EXPECT_TRUE(resultIsGamePaused);
}
