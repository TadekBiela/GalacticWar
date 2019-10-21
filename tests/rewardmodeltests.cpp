#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/rewardmodel.hpp"
#include <QTimer>
#include <QGraphicsScene>

class RewardModelTest : public RewardModel
{
public:
    RewardModelTest() {}
    virtual ~RewardModelTest() {}

    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }

// dummy implementation
    void collect() {}
public slots:
    void animation() {}
};

class RewardModelTestsClass : public testing::Test
{

};

TEST_F(RewardModelTestsClass, RewardModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardModelTest rewardModel;
    int           resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardModel.getAnimationTimer();
    int           resultAnimTime     = resultAnimTimer.remainingTime();
    const QTimer& resultDestroyTimer = rewardModel.getDestroyTimer();
    int           resultDestroyTime  = resultDestroyTimer.remainingTime();

    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
    EXPECT_NEAR(resultAnimTime,                    def::animationFrameDuration, 1);
    EXPECT_NEAR(resultDestroyTime,                 def::defaultRewardDestroyTimeDelay, 1);
}

TEST_F(RewardModelTestsClass, Destroy_CheckCorrectWorking_IsZero)
{
    QGraphicsScene   scene;
    RewardModelTest* rewardModel = new RewardModelTest;
    scene.addItem(rewardModel);
    int resultShouldBeOne = scene.items().size();

    rewardModel->destroy();
    int resultShouldBeZero = scene.items().size();

    EXPECT_EQ(resultShouldBeOne,  1);
    EXPECT_EQ(resultShouldBeZero, 0);
}
