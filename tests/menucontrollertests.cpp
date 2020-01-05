#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/menucontroller.hpp"
#include "../app/menumodel.hpp"
#include "../app/generalview.hpp"
#include "stubs/filemanagerstub.hpp"
#include <QSignalSpy>

class MenuControllerTest : public MenuController
{
public:
    MenuControllerTest(GeneralView* view,
                       MenuModel*   model)
                        : MenuController(view,
                                         model) {}
    virtual ~MenuControllerTest() {}

    bool getIsGamePaused() const { return m_isGamePaused; }
    void setIsGamePaused(bool value) { m_isGamePaused = value; }
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

TEST_F(MenuControllerTestsClass, StartGame_CheckIfWillBeSendSignalsToResetLevelAndScoreAndCreateNewPlayerModel_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalResetLevel(&menuController, &MenuControllerTest::resetLevel);
    QSignalSpy signalResetScore(&menuController, &MenuControllerTest::resetScore);
    QSignalSpy signalCreate(&menuController,     &MenuControllerTest::createNewPlayer);
    signalCreate.wait(utdef::minSignalTimeDelay);

    menuController.startGame();
    int resultSignalResetLevelCount = signalResetLevel.count();
    int resultSignalResetScoreCount = signalResetScore.count();
    int resultSignalCreateCount     = signalCreate.count();

    EXPECT_EQ(resultSignalResetLevelCount, 1);
    EXPECT_EQ(resultSignalResetScoreCount, 1);
    EXPECT_EQ(resultSignalCreateCount,     1);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, EscPressed_EscapePressedOneOnGameShouldPauseAllGameElementsBySendSignals_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalPause(&menuController, &MenuControllerTest::pauseGame);
    QSignalSpy signalDeactivate(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    signalPause.wait(utdef::minSignalTimeDelay);
    bool defaultIsGamePaused = menuController.getIsGamePaused();

    menuController.escPressed();
    bool reslutIsGamePaused          = menuController.getIsGamePaused();
    int  resultSignalPauseCount      = signalPause.count();
    int  resultSignalDeactivateCount = signalDeactivate.count();

    EXPECT_FALSE(defaultIsGamePaused);
    EXPECT_TRUE(reslutIsGamePaused);
    EXPECT_EQ(resultSignalPauseCount,      1);
    EXPECT_EQ(resultSignalDeactivateCount, 1);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, EscPressed_EscapePressedOneOnPauseShouldContinueAllGameElementsBySendSignals_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalContinue(&menuController, &MenuControllerTest::continueGame);
    QSignalSpy signalActivate(&menuController, &MenuControllerTest::activateEnemySpawning);
    signalContinue.wait(utdef::minSignalTimeDelay);
    menuController.setIsGamePaused(true); //Pause enabled

    menuController.escPressed();
    bool reslutIsGamePaused        = menuController.getIsGamePaused();
    int  resultSignalPauseCount    = signalContinue.count();
    int  resultSignalActivateCount = signalActivate.count();

    EXPECT_FALSE(reslutIsGamePaused);
    EXPECT_EQ(resultSignalPauseCount,    1);
    EXPECT_EQ(resultSignalActivateCount, 1);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, UpdateScore_CheckIfBeSendignalToStopAllGameAndSwitchViewToGameOver_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalPlayerDef(&menuController, &MenuControllerTest::playerDefeated);
    signalPlayerDef.wait(utdef::minSignalTimeDelay);

    menuController.updateScore(240);
    int resultSignalPlayerDefCount     = signalPlayerDef.count();
    int resutlScoreFromPlayerDefSignal = signalPlayerDef.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalPlayerDefCount,       1);
    EXPECT_EQ(resutlScoreFromPlayerDefSignal, 240);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, GameOver_CheckIfBeSendSignalToStopSpawningEnemies_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalDeactEnemySpawn(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    signalDeactEnemySpawn.wait(utdef::minSignalTimeDelay);

    menuController.gameOver();
    int resultSignalDeactEnemySpawnCount = signalDeactEnemySpawn.count();

    EXPECT_EQ(resultSignalDeactEnemySpawnCount, 1);
    delete model;
    delete fileMgr;
    delete view;
}
