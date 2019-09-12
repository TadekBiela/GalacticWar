#include <gtest/gtest.h>
#include "../app/scoreview.hpp"
#include <QProgressBar>

class ScoreViewTests : public ScoreView
{
public:
    const QProgressBar& getScoreBar() { return m_scoreBar; }
};

class ScoreViewTestsClass : public testing::Test
{
};

TEST_F(ScoreViewTestsClass, Update_UpdateWithValue0_IsZero)
{
    ScoreViewTests scoreView;

    scoreView.update(0);
    const QProgressBar& resultScoreBar = scoreView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 0);
}

TEST_F(ScoreViewTestsClass, Update_UpdateWithValue30_IsEqual)
{
    ScoreViewTests scoreView;

    scoreView.update(30);
    const QProgressBar& resultScoreBar = scoreView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 30);
}

TEST_F(ScoreViewTestsClass, Update_UpdateWithMaxValue_IsEqual)
{
    ScoreViewTests scoreView;

    scoreView.update(100);
    const QProgressBar& resultScoreBar = scoreView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 100);
}

TEST_F(ScoreViewTestsClass, Update_UpdateWithMoreThanMaxValueShouldntIncreaseMoreThanMax_IsEqual)
{
    ScoreViewTests scoreView;

    scoreView.update(120);
    const QProgressBar& resultScoreBar = scoreView.getScoreBar();

    EXPECT_EQ(resultScoreBar.value(), 100);
}
