#include <gtest/gtest.h>
#include "../app/levelview.hpp"
#include "../app/definitions.hpp"
#include <QLabel>
#include <QString>

class LevelViewTests : public LevelView
{
public:
    const QLabel& getLevelLabel() { return m_levelLabel; }
};

class LevelViewTestsClass : public testing::Test
{
};

TEST_F(LevelViewTestsClass, Update_UpdateWithValue1_IsOne)
{
    LevelViewTests levelView;

    levelView.update(1);
    const QLabel& resultLevelLabel = levelView.getLevelLabel();

    EXPECT_EQ(resultLevelLabel.text().toStdString(), "1");
}

TEST_F(LevelViewTestsClass, Update_UpdateWithValueMax_IsEqual)
{
    LevelViewTests levelView;

    levelView.update(def::maxNumOfLevel);
    const QLabel& resultLevelLabel = levelView.getLevelLabel();

    EXPECT_EQ(resultLevelLabel.text().toStdString(), "10");
}
