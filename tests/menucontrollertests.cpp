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
    MenuControllerTest(GeneralView* generalView,
                       MenuModel*   menuModel) :
                       MenuController(generalView,
                                      menuModel) {}
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
    QSignalSpy signalActEnemySpawn(&menuController, &MenuControllerTest::activateEnemySpawning);
    signalActEnemySpawn.wait(utdef::minSignalTimeDelay);

    menuController.startGame();
    int resultSignalActEnemySpawnCount = signalActEnemySpawn.count();

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

TEST_F(MenuControllerTestsClass, GameOver_CheckIfBeSendTwoSignalsToStopAllGameAndSwitchViewToGameOver_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalDeactEnemySpawn(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    QSignalSpy signalPlayerDef(&menuController, &MenuControllerTest::playerDefeated);
    signalPlayerDef.wait(utdef::minSignalTimeDelay);

    menuController.gameOver();
    int resultSignalDeactEnemySpawnCount = signalDeactEnemySpawn.count();
    int resultSignalPlayerDefCount       = signalPlayerDef.count();

    EXPECT_EQ(resultSignalDeactEnemySpawnCount, 1);
    EXPECT_EQ(resultSignalPlayerDefCount,       1);
    delete model;
    delete fileMgr;
    delete view;
}
