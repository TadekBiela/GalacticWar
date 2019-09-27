#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/levelcontroller.hpp"
#include "../app/levelmodel.hpp"
#include "../app/levelview.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(EnemyConfiguration)

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
    int resultSignalNextLevelCount = signalNext.count();

    EXPECT_EQ(resultSignalNextLevelCount, 1);
    delete model;
    delete view;
}

TEST_F(LevelControllerTestsClass, ChangeEnemyConfig_CheckIfWillSendChangeEnemyConfigurationSignalOneTime_IsEqual)
{
    qRegisterMetaType<EnemyConfiguration>();
    EnemyConfiguration inputEnemyConfig = { 10, 50, 0, 25, 15, 0 };
    LevelModel* model = new LevelModel;
    LevelView*  view  = new LevelView;
    LevelControllerTest levelController(model, view);
    QSignalSpy signalChange(&levelController, &LevelControllerTest::changeEnemyConfiguration);
    signalChange.wait(utdef::minSignalTimeDelay);

    levelController.changeEnemyConfig(inputEnemyConfig);
    int                resultSignalAddCount = signalChange.count();
    EnemyConfiguration resultEnemyConfig    = qvariant_cast<EnemyConfiguration>(signalChange.takeFirst().at(0));

    EXPECT_EQ(resultSignalAddCount,                     1);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType1, inputEnemyConfig.proportionOfEnemyType1);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType2, inputEnemyConfig.proportionOfEnemyType2);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType3, inputEnemyConfig.proportionOfEnemyType3);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType4, inputEnemyConfig.proportionOfEnemyType4);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType5, inputEnemyConfig.proportionOfEnemyType5);
    EXPECT_EQ(resultEnemyConfig.proportionOfEnemyType6, inputEnemyConfig.proportionOfEnemyType6);
    delete model;
    delete view;
}
