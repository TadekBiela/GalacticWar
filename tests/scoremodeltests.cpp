#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/scoremodel.hpp"
#include <QSignalSpy>

class ScoreModelTests : public ScoreModel
{
public:
    int getCurrentTresholdIdx() const   { return m_currentTresholdIdx; }
    int getTotalScore()           const { return m_totalScore; }
    void setCurrentTresholdIdx(int idx) { m_currentTresholdIdx = idx; }
    void setTotalScore(int score)       { m_totalScore = score; }
};

class ScoreModelTestsClass : public testing::Test
{
};

TEST_F(ScoreModelTestsClass, ScoreModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    ScoreModelTests scoreModel;
    int resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();
    int resultTotalScore           = scoreModel.getTotalScore();

    EXPECT_EQ(resultCurrentTresholdIdx, 0);
    EXPECT_EQ(resultTotalScore,         0);
}

TEST_F(ScoreModelTestsClass, AddScorePoints_AddPointsLessThanFirstTresholdShouldOnlyEmitOneSignal_IsEqual)
{
    ScoreModelTests scoreModel;
    QSignalSpy      signalUpdate(&scoreModel, ScoreModelTests::updateScoreView);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreModel.addScorePoints(300);
    int  resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();
    int  resultTotalScore         = scoreModel.getTotalScore();
    int  resultSignalUpdateCount  = signalUpdate.count();
    auto resultSignalUpdate       = signalUpdate.takeFirst();

    EXPECT_EQ(resultCurrentTresholdIdx,         0);
    EXPECT_EQ(resultTotalScore,                 300);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).toInt(), 30);
}

TEST_F(ScoreModelTestsClass, AddScorePoints_AddPointsMoreThanFirstTresholdShouldEmitTwoSignals_IsEqual)
{
    ScoreModelTests scoreModel;
    QSignalSpy      signalUpdate(&scoreModel,  ScoreModelTests::updateScoreView);
    QSignalSpy      signalAchived(&scoreModel, ScoreModelTests::maxScorePerLevelAchieved);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreModel.addScorePoints(1200);
    int  resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();
    int  resultTotalScore         = scoreModel.getTotalScore();
    int  resultSignalUpdateCount  = signalUpdate.count();
    auto resultSignalUpdate       = signalUpdate.takeFirst();
    int  resultSignalAchivedCount = signalAchived.count();

    EXPECT_EQ(resultCurrentTresholdIdx,         1);
    EXPECT_EQ(resultTotalScore,                 1200);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).toInt(), 10);
    EXPECT_EQ(resultSignalAchivedCount,         1);
}

TEST_F(ScoreModelTestsClass, AddScorePoints_AddPointsEqualThanThirdTresholdShouldEmitTwoSignals_IsEqual)
{
    ScoreModelTests scoreModel;
    scoreModel.setCurrentTresholdIdx(2);
    scoreModel.setTotalScore(6500);
    QSignalSpy      signalUpdate(&scoreModel,  ScoreModelTests::updateScoreView);
    QSignalSpy      signalAchived(&scoreModel, ScoreModelTests::maxScorePerLevelAchieved);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreModel.addScorePoints(500);
    int  resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();
    int  resultTotalScore         = scoreModel.getTotalScore();
    int  resultSignalUpdateCount  = signalUpdate.count();
    auto resultSignalUpdate       = signalUpdate.takeFirst();
    int  resultSignalAchivedCount = signalAchived.count();

    EXPECT_EQ(resultCurrentTresholdIdx,         3);
    EXPECT_EQ(resultTotalScore,                 7000);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).toInt(), 0);
    EXPECT_EQ(resultSignalAchivedCount,         1);
}

TEST_F(ScoreModelTestsClass, AddScorePoints_AddPointsMoreThanMaxTresholdShouldEmitOneSignal_IsEqual)
{
    ScoreModelTests scoreModel;
    scoreModel.setCurrentTresholdIdx(9);
    scoreModel.setTotalScore(299900);
    QSignalSpy      signalUpdate(&scoreModel,  ScoreModelTests::updateScoreView);
    QSignalSpy      signalAchived(&scoreModel, ScoreModelTests::maxScorePerLevelAchieved);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreModel.addScorePoints(500);
    int  resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();
    int  resultTotalScore         = scoreModel.getTotalScore();
    int  resultSignalUpdateCount  = signalUpdate.count();
    auto resultSignalUpdate       = signalUpdate.takeFirst();
    int  resultSignalAchivedCount = signalAchived.count();

    EXPECT_EQ(resultCurrentTresholdIdx,         9);
    EXPECT_EQ(resultTotalScore,                 300400);
    EXPECT_EQ(resultSignalUpdateCount,          1);
    EXPECT_EQ(resultSignalUpdate.at(0).toInt(), 100);
    EXPECT_EQ(resultSignalAchivedCount,         0);
}
