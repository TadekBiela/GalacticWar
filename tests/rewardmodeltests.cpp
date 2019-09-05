#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/rewardtype.hpp"
#include "../app/rewardmodel.hpp"
#include <QTimer>

class RewardModelTest : public RewardModel
{
public:
    RewardModelTest(reward_type type) :
                    RewardModel(type) {}

    reward_type   getType()              const { return m_type; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }

public slots:
    void animation() {} // dummy implementation
};

class RewardModelTestsClass : public testing::Test
{

};

TEST_F(RewardModelTestsClass, RewardModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardModelTest rewardModel(reward_type::rewardCoin);
    reward_type   resultType         = rewardModel.getType();
    int           resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardModel.getDestroyTimer();
    int           resultAnimTime     = resultAnimTimer.remainingTime();
    int           resultDestroyTime  = resultDestroyTimer.remainingTime();

    EXPECT_EQ(resultType,                          reward_type::rewardCoin);
    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
    EXPECT_NEAR(resultAnimTime,                    def::animationFrameDuration, 1);
    EXPECT_NEAR(resultDestroyTime,                 def::defaultRewardDestroyTimeDelay, 1);
}
