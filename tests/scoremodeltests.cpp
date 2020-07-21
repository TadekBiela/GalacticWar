#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/scoremodel.hpp"
#include <QSignalSpy>

class ScoreModelTest : public ScoreModel
{
public:
    ScoreModelTest() {}
    virtual ~ScoreModelTest() {}

    int  getCurrentTresholdIdx() const  { return m_currentTresholdIdx; }
    int  getCurrentScore()       const  { return m_currentScore; }
    int  getTotalScore()         const  { return m_totalScore; }
    void setCurrentTresholdIdx(int idx) { m_currentTresholdIdx = idx; }
    void setCurrentScore(int score)     { m_currentScore = score; }
    void setTotalScore(int score)       { m_totalScore = score; }
};

class ScoreModelTestsClass : public testing::Test
{
};

TEST_F(ScoreModelTestsClass, Add_CurrentScoreIs0Add10Points_CurrentAndTotalScoreShouldIncreaseBy10CurrentTreshold0AndScoreStatusCurrentLevel)
{
    ScoreModelTest scoreModel;

    Score_Per_Level resultStatus = scoreModel.add(10);
    int resultCurrentScore       = scoreModel.getCurrentScore();
    int resultTotalScore         = scoreModel.getTotalScore();
    int resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();

    EXPECT_EQ(10, resultCurrentScore);
    EXPECT_EQ(10, resultTotalScore);
    EXPECT_EQ(0, resultCurrentTresholdIdx);
    EXPECT_EQ(Score_Per_Level_Current, resultStatus);
}

TEST_F(ScoreModelTestsClass, Add_CurrentScoreIsLessThanFirstTresholdBy10Add50Points_CurrentScoreSouldBe40TotalScoreFirstTresholdPlus40CurrentTreshold1AndScoreStatusNextLevel)
{
    ScoreModelTest scoreModel;
    int firstTresholdValue = scoreModel.getCurrentTreshold();
    scoreModel.setCurrentScore(firstTresholdValue - 10);
    scoreModel.setTotalScore(firstTresholdValue - 10);

    Score_Per_Level resultStatus = scoreModel.add(50);
    int resultCurrentScore       = scoreModel.getCurrentScore();
    int resultTotalScore         = scoreModel.getTotalScore();
    int resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();

    EXPECT_EQ(40,                      resultCurrentScore);
    EXPECT_EQ(firstTresholdValue + 40, resultTotalScore);
    EXPECT_EQ(1,                       resultCurrentTresholdIdx);
    EXPECT_EQ(Score_Per_Level_Next,    resultStatus);
}

TEST_F(ScoreModelTestsClass, Add_CurrentScoreIsLessThanLastTresholdBy10Add50Points_CurrentAndTotalScoreSouldBeIncresaedBy40CurrentTresholdStillLastAndScoreStatusCurrentLevel)
{
    ScoreModelTest scoreModel;
    scoreModel.setCurrentTresholdIdx(def::maxNumOfLevel - 1);
    int lastTresholdValue = scoreModel.getCurrentTreshold();
    scoreModel.setCurrentScore(lastTresholdValue - 10);
    scoreModel.setTotalScore(lastTresholdValue - 10);

    Score_Per_Level resultStatus = scoreModel.add(50);
    int resultCurrentScore       = scoreModel.getCurrentScore();
    int resultTotalScore         = scoreModel.getTotalScore();
    int resultCurrentTresholdIdx = scoreModel.getCurrentTresholdIdx();

    EXPECT_EQ(lastTresholdValue + 40,  resultCurrentScore);
    EXPECT_EQ(lastTresholdValue + 40,  resultTotalScore);
    EXPECT_EQ(def::maxNumOfLevel - 1,  resultCurrentTresholdIdx);
    EXPECT_EQ(Score_Per_Level_Current, resultStatus);
}
