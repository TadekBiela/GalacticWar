#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardtypes.hpp"
#include <QTimer>
#include <QGraphicsScene>

class RewardCoinModelTest : public RewardCoinModel
{
public:
    RewardCoinModelTest(coin_type type) :
                        RewardCoinModel(type) {}

    coin_type     getType()              const { return m_type; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }
    void          setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
};

class RewardCoinModelTestsClass : public testing::Test
{
};

TEST_F(RewardCoinModelTestsClass, RewardCoinModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardCoinModelTest rewardCoinModel(coin_type::bronze);
    coin_type     resultType         = rewardCoinModel.getType();
    int           resultAnimFrameIdx = rewardCoinModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardCoinModel.getAnimationTimer();
    int           resultAnimTime     = resultAnimTimer.remainingTime();
    const QTimer& resultDestroyTimer = rewardCoinModel.getDestroyTimer();
    int           resultDestroyTime  = resultDestroyTimer.remainingTime();

    EXPECT_EQ(resultType,                          coin_type::bronze);
    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
    EXPECT_NEAR(resultAnimTime,                    def::animationFrameDuration, 1);
    EXPECT_NEAR(resultDestroyTime,                 def::defaultRewardDestroyTimeDelay, 1);
}

TEST_F(RewardCoinModelTestsClass, Animation_AnimationFrameIdxIs0CheckIfWillBeIncreased_IsOne)
{
    RewardCoinModelTest rewardCoinModel(coin_type::bronze);

    rewardCoinModel.animation();
    int resultAnimFrameIdx = rewardCoinModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 1);
}

TEST_F(RewardCoinModelTestsClass, Animation_AnimationFrameIdxIsMaxCheckIfWillBeResetTo0_IsZero)
{
    RewardCoinModelTest rewardCoinModel(coin_type::bronze);
    rewardCoinModel.setAnimationFrameIdx(def::maxAnimationFrameIdx);

    rewardCoinModel.animation();
    int resultAnimFrameIdx = rewardCoinModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 0);
}
