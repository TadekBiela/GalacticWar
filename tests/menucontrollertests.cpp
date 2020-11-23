#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/backgroundmusicplayerstub.hpp"
#include "stubs/filemanagerstub.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/backgroundmusicplayer.hpp"
#include "../app/menucontroller.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/controlplane.hpp"
#include "../app/gameplayview.hpp"
#include <QWidget>
#include <QSignalSpy>

class MenuControllerTest : public MenuController
{
public:
    MenuControllerTest(
        QWidget* displayWidget,
        ControlPlane* controller,
        GameplayView* gameplayView,
        AnimationPlaneView* animationView,
        BackgroundMusicPlayerStub* backgroundMusicPlayerStub
    ) :
        MenuController(
            displayWidget,
            controller,
            gameplayView,
            animationView,
            backgroundMusicPlayerStub,
            g_soundStorage,
            new FileManagerStub()
        )
    {}
    virtual ~MenuControllerTest() {}
    int getHighscoreSize() {
        return m_model.getHighscoreSize();
    }
    void setPlayerNameFieldInView(QString playerName) {
        m_view.setPlayerNameField(playerName);
    }
};

class MenuControllerTestsClass : public testing::Test
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(MenuControllerTestsClass, PauseGame_CheckCorrectWorking_ShouldSendGamePauseSignal)
{
    QWidget displayWidget;
    ControlPlane controller(&displayWidget);
    GameplayView gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    NiceMock<BackgroundMusicPlayerStub> backgroundMusicPlayerStub;
    MenuControllerTest menuController(
        &displayWidget,
        &controller,
        &gameplayView,
        &animationView,
        &backgroundMusicPlayerStub
    );
    QSignalSpy signalGamePaused(
        &menuController,
        &MenuControllerTest::gamePaused
    );
    signalGamePaused.wait(utdef::minSignalTimeDelay);

    menuController.pauseGame();

    EXPECT_EQ(1, signalGamePaused.count());
}

TEST_F(MenuControllerTestsClass, SaveScore_PlayerNameIsFilled_ShouldSavePlayerScore)
{
    QWidget displayWidget;
    ControlPlane controller(&displayWidget);
    GameplayView gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    NiceMock<BackgroundMusicPlayerStub> backgroundMusicPlayerStub;
    MenuControllerTest menuController(
        &displayWidget,
        &controller,
        &gameplayView,
        &animationView,
        &backgroundMusicPlayerStub
    );
    menuController.setPlayerNameFieldInView("test");

    menuController.saveScore();

    EXPECT_EQ(1, menuController.getHighscoreSize());
}

TEST_F(MenuControllerTestsClass, SaveScore_PlayerNameIsEmpty_ShouldDontSavePlayerScore)
{
    QWidget displayWidget;
    ControlPlane controller(&displayWidget);
    GameplayView gameplayView(&displayWidget);
    AnimationPlaneView animationView(&displayWidget);
    NiceMock<BackgroundMusicPlayerStub> backgroundMusicPlayerStub;
    MenuControllerTest menuController(
        &displayWidget,
        &controller,
        &gameplayView,
        &animationView,
        &backgroundMusicPlayerStub
    );
    menuController.setPlayerNameFieldInView("");

    menuController.saveScore();

    EXPECT_EQ(0, menuController.getHighscoreSize());
}
