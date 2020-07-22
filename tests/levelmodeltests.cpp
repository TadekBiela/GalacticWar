#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/enemyconfiguration.hpp"
#include "../app/levelmodel.hpp"

class LevelModelTests : public LevelModel
{
public:
    LevelModelTests() {}
    virtual ~LevelModelTests() {}

    void setCurrentLevel(int value) { m_currentLevel = value; }
};

class LevelModelTestsClass : public testing::Test
{
};

TEST_F(LevelModelTestsClass, Next_CurrentLevelIs1_ShouldIncreaseCurrentLevelTo2)
{
    LevelModelTests levelModel;

    levelModel.next();
    int resultCurrentLevel = levelModel.getCurrentLevel();

    EXPECT_EQ(2, resultCurrentLevel);
}

TEST_F(LevelModelTestsClass, Next_CurrentLevelIsMax_ShouldDoNothing)
{
    LevelModelTests levelModel;
    levelModel.setCurrentLevel(def::maxNumOfLevel);

    levelModel.next();
    int resultCurrentLevel = levelModel.getCurrentLevel();

    EXPECT_EQ(def::maxNumOfLevel, resultCurrentLevel);
}
