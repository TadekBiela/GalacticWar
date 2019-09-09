#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/rewardspecialmodel.hpp"
#include "../app/rewardtypes.hpp"
#include <QTimer>
#include <QGraphicsScene>
#include <QSignalSpy>

Q_DECLARE_METATYPE(special_type)

class RewardSpecialModelTest : public RewardSpecialModel
{
public:
    RewardSpecialModelTest(special_type type) :
                           RewardSpecialModel(type) {}

    special_type  getType()              const { return m_type; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }
    void          setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
};

class RewardSpecialModelTestsClass : public testing::Test
{
};

TEST_F(RewardSpecialModelTestsClass, RewardSpecialModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardSpecialModelTest rewardSpecialModel(special_type::health);
    special_type  resultType         = rewardSpecialModel.getType();
    int           resultAnimFrameIdx = rewardSpecialModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardSpecialModel.getAnimationTimer();
    int           resultAnimTime     = resultAnimTimer.remainingTime();
    const QTimer& resultDestroyTimer = rewardSpecialModel.getDestroyTimer();
    int           resultDestroyTime  = resultDestroyTimer.remainingTime();

    EXPECT_EQ(resultType,                          special_type::health);
    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
    EXPECT_NEAR(resultAnimTime,                    def::animationFrameDuration,        1);
    EXPECT_NEAR(resultDestroyTime,                 def::defaultRewardDestroyTimeDelay, 1);
}

TEST_F(RewardSpecialModelTestsClass, Animation_AnimationFrameIdxIs0CheckIfWillBeIncreased_IsOne)
{
    RewardSpecialModelTest rewardSpecialModel(special_type::health);

    rewardSpecialModel.animation();
    int resultAnimFrameIdx = rewardSpecialModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 1);
}

TEST_F(RewardSpecialModelTestsClass, Animation_AnimationFrameIdxIsMaxCheckIfWillBeResetTo0_IsZero)
{
    RewardSpecialModelTest rewardSpecialModel(special_type::health);
    rewardSpecialModel.setAnimationFrameIdx(def::maxAnimationFrameIdx);

    rewardSpecialModel.animation();
    int resultAnimFrameIdx = rewardSpecialModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 0);
}

TEST_F(RewardSpecialModelTestsClass, Animation_AnimationFrameIdxIsMaxMinusOneCheckIfWillBeSetToMax_IsEqual)
{
    RewardSpecialModelTest rewardSpecialModel(special_type::health);
    rewardSpecialModel.setAnimationFrameIdx(def::maxAnimationFrameIdx - 1);

    rewardSpecialModel.animation();
    int resultAnimFrameIdx = rewardSpecialModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, def::maxAnimationFrameIdx);
}

TEST_F(RewardSpecialModelTestsClass, Collect_CheckIfWillBeSendSignalWithCorrectType_IsEqual)
{
    qRegisterMetaType<special_type>();
    QGraphicsScene          scene;
    RewardSpecialModelTest* rewardSpecialModel = new RewardSpecialModelTest(special_type::weaponYellow);
    scene.addItem(rewardSpecialModel);
    int resultShouldBeOne = scene.items().size();
    QSignalSpy signalCollect(rewardSpecialModel, &RewardSpecialModelTest::collected);
    signalCollect.wait(utdef::minSignalTimeDelay);

    rewardSpecialModel->collect();
    int             resultSignalCollectCount = signalCollect.count();
    QList<QVariant> resultSignalCollect      = signalCollect.takeFirst();
    special_type    resultType               = qvariant_cast<special_type>(resultSignalCollect.at(0));
    int             resultShouldBeZero       = scene.items().size();

    EXPECT_EQ(resultSignalCollectCount, 1);
    EXPECT_EQ(resultType,               special_type::weaponYellow);
    EXPECT_EQ(resultShouldBeOne,        1);
    EXPECT_EQ(resultShouldBeZero,       0);
}
