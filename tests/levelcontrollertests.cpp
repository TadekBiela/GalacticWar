#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/levelcontroller.hpp"
#include "../app/levelmodel.hpp"
#include "../app/levelview.hpp"
#include <QSignalSpy>

class LevelControllerTest : public LevelController
{
public:
    LevelControllerTest(LevelModel* levelModel,
                        LevelView*  levelView) :
                        LevelController(levelModel,
                                        levelView) {}
};

class LevelControllerTestsClass : public testing::Test
{
};

TEST_F(LevelControllerTestsClass, NextLevel_CheckIfWillSendNextLevelInModelSignalOneTime_IsEqual)
{
    LevelModel* model = new LevelModel;
    LevelView*  view  = new LevelView;
    LevelControllerTest levelController(model, view);
    QSignalSpy signalNext(&levelController, &LevelControllerTest::nextLevelInModel);
    signalNext.wait(utdef::minSignalTimeDelay);

    levelController.nextLevel();
    int resultSignalAddCount = signalNext.count();

    EXPECT_EQ(resultSignalAddCount, 1);
    delete model;
    delete view;
}
