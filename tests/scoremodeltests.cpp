#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/scoremodel.hpp"
#include <QSignalSpy>

class ScoreModelTests : public ScoreModel
{
public:
    int getCurrentTresholdIdx() const { return m_currentTresholdIdx; }
    int getTotalScore()           const { return m_totalScore; }
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
