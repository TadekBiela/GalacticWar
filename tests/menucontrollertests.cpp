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

TEST_F(MenuControllerTestsClass, StartGame_CheckIfWillBeSendTwoSignalsToActivatePlayerAndEnemies_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalActEnemySpawn(&menuController, &MenuControllerTest::activateEnemySpawning);
    QSignalSpy signalActPlayer(&menuController, &MenuControllerTest::activatePlayer);
    signalActPlayer.wait(utdef::minSignalTimeDelay);

    menuController.startGame();
    int resultSignalActEnemySpawnCount = signalActEnemySpawn.count();
    int resultSignalActPlayerCount     = signalActPlayer.count();

    EXPECT_EQ(resultSignalActEnemySpawnCount, 1);
    EXPECT_EQ(resultSignalActPlayerCount,     1);
    delete model;
    delete fileMgr;
    delete view;
}

TEST_F(MenuControllerTestsClass, StopGame_CheckIfWillBeSendTwoSignalsToDeactivatePlayerAndEnemies_IsEqual)
{
    FileManagerStub*   fileMgr = new FileManagerStub;
    MenuModel*         model   = new MenuModel(fileMgr);
    GeneralView*       view    = new GeneralView;
    MenuControllerTest menuController(view, model);
    QSignalSpy signalDeactEnemySpawn(&menuController, &MenuControllerTest::deactivateEnemySpawning);
    QSignalSpy signalDeactPlayer(&menuController, &MenuControllerTest::deactivatePlayer);
    signalDeactPlayer.wait(utdef::minSignalTimeDelay);

    menuController.stopGame();
    int resultSignalDeactEnemySpawnCount = signalDeactEnemySpawn.count();
    int resultSignalDeactPlayerCount     = signalDeactPlayer.count();

    EXPECT_EQ(resultSignalDeactEnemySpawnCount, 1);
    EXPECT_EQ(resultSignalDeactPlayerCount,     1);
    delete model;
    delete fileMgr;
    delete view;
}
