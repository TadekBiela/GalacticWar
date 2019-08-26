#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/enemyconfiguration.hpp"
#include "../app/levelmodel.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(EnemyConfiguration)

class LevelModelTests : public LevelModel
{
public:
    int getCurrentLevel() const { return m_currentLevel; }
    void setCurrentLevel(int value) { m_currentLevel = value; }
};

class LevelModelTestsClass : public testing::Test
{
};

TEST_F(LevelModelTestsClass, NextLevel_CurrentLevelShouldIncreaseAndSentTwoDifferentSignals_IsEqual)
{
    EnemyConfiguration expectedEnemyLevelConfig = { 50, 40, 10,  0,  0,  0 };
    LevelModelTests    levelModel;
    QSignalSpy         signalUpdate(&levelModel, &LevelModelTests::updateLevelView);
    qRegisterMetaType<EnemyConfiguration>();
    QSignalSpy         signalChange(&levelModel, &LevelModelTests::changeEnemyModelConfiguration);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    levelModel.nextLevel();
    int                resultCurrentLevel      = levelModel.getCurrentLevel();
    int                resultSignalUpdateCount = signalUpdate.count();
    int                resultSignalChangeCount = signalChange.count();
    QList<QVariant>    resultSignalUpdate      = signalUpdate.takeFirst();
    QList<QVariant>    resultSignal2Change     = signalChange.takeFirst();
    EnemyConfiguration resultEnemyLevelConfig  = qvariant_cast<EnemyConfiguration>(resultSignal2Change.at(0));

    EXPECT_EQ(resultCurrentLevel,               2);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).toInt(), 2);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType1, expectedEnemyLevelConfig.proportionOfEnemyType1);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType2, expectedEnemyLevelConfig.proportionOfEnemyType2);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType3, expectedEnemyLevelConfig.proportionOfEnemyType3);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType4, expectedEnemyLevelConfig.proportionOfEnemyType4);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType5, expectedEnemyLevelConfig.proportionOfEnemyType5);
    EXPECT_EQ(resultEnemyLevelConfig.proportionOfEnemyType6, expectedEnemyLevelConfig.proportionOfEnemyType6);
}

TEST_F(LevelModelTestsClass, NextLevel_CurrentLevelIsMaxShouldDontIncreaseAndSentAnySignals_IsEqual)
{
    LevelModelTests levelModel;
    levelModel.setCurrentLevel(def::maxNumOfLevel);
    QSignalSpy      signalUpdate(&levelModel, &LevelModelTests::updateLevelView);
    qRegisterMetaType<EnemyConfiguration>();
    QSignalSpy      signalChange(&levelModel, &LevelModelTests::changeEnemyModelConfiguration);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    levelModel.nextLevel();
    int resultCurrentLevel      = levelModel.getCurrentLevel();
    int resultSignalUpdateCount = signalUpdate.count();
    int resultSignalChangeCount = signalChange.count();

    EXPECT_EQ(resultCurrentLevel,      10);
    EXPECT_EQ(resultSignalUpdateCount, 0);
    EXPECT_EQ(resultSignalChangeCount, 0);
}
