#include <gtest/gtest.h>
#include "utdefinitions.hpp"
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
};

class MenuControllerTestsClass : public testing::Test
{
};

TEST_F(MenuControllerTestsClass, StartGame_CheckIfWillBeSendSignalToActivateEnemies_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalResetLevel(&menuController,    &MenuControllerTest::resetLevel);
    QSignalSpy signalResetScore(&menuController,    &MenuControllerTest::resetScore);
    QSignalSpy signalCreate(&menuController,        &MenuControllerTest::createNewPlayer);
    QSignalSpy signalActEnemySpawn(&menuController, &MenuControllerTest::activateEnemySpawning);
    signalActEnemySpawn.wait(utdef::minSignalTimeDelay);

    menuController.startGame();
    int resultSignalResetLevelCount    = signalResetLevel.count();
    int resultSignalResetScoreCount    = signalResetScore.count();
    int resultSignalCreateCount        = signalCreate.count();
    int resultSignalActEnemySpawnCount = signalActEnemySpawn.count();

    EXPECT_EQ(resultSignalResetLevelCount,    1);
    EXPECT_EQ(resultSignalResetScoreCount,    1);
    EXPECT_EQ(resultSignalCreateCount,        1);
    EXPECT_EQ(resultSignalActEnemySpawnCount, 1);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, StopGame_CheckIfWillBeSendSignalToDeactivateEnemies_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalDeactEnemySpawn(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    signalDeactEnemySpawn.wait(utdef::minSignalTimeDelay);

    menuController.stopGame();
    int resultSignalDeactEnemySpawnCount = signalDeactEnemySpawn.count();

    EXPECT_EQ(resultSignalDeactEnemySpawnCount, 1);
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

    EXPECT_EQ(resultSignalPlayerDefCount,     1);
    EXPECT_EQ(resutlScoreFromPlayerDefSignal, 240);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, GameOver_CheckIfBeSendTwoSignalsToStopAllGameAndGetScoreFromScoreController_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalDeactEnemySpawn(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    QSignalSpy signalGetScore(&menuController, &MenuControllerTest::getScore);
    signalGetScore.wait(utdef::minSignalTimeDelay);

    menuController.gameOver();
    int resultSignalDeactEnemySpawnCount = signalDeactEnemySpawn.count();
    int resultSignalPlayerDefCount       = signalGetScore.count();

    EXPECT_EQ(resultSignalDeactEnemySpawnCount, 1);
    EXPECT_EQ(resultSignalPlayerDefCount,       1);
    delete model;
    delete fileMgr;
    delete view;
}
