#include <gtest/gtest.h>
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/animationeffectmodel.hpp"
#include "../app/rewardmodel.hpp"
#include <QTimer>
#include <QGraphicsScene>

class RewardModelTest : public RewardModel
{
public:
    RewardModelTest()
    {
        //Simple graphic needed to tests
        QPixmap map(QSize(def::animationSmallFrameWidth, def::animationSmallFrameHeight));
        map.fill(Qt::red);
        setPixmap(map);
    }
    virtual ~RewardModelTest() {}
    void setImage(QImage* image) { m_image = image; }

    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }
    void          setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }

// dummy implementation
    void collect() {}
};

class RewardModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(RewardModelTestsClass, RewardModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardModelTest rewardModel;
    int           resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardModel.getDestroyTimer();

    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
}

TEST_F(RewardModelTestsClass, Start_CheckIfAllTimersWillBeActive_IsEqual)
{
    RewardModelTest rewardModel;

    rewardModel.start();
    const QTimer& resultAnimTimer    = rewardModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardModel.getDestroyTimer();

    EXPECT_EQ(resultAnimTimer.isActive(),    true);
    EXPECT_EQ(resultDestroyTimer.isActive(), true);
}

TEST_F(RewardModelTestsClass, Stop_CheckIfAllTimersWillBeNotActive_IsEqual)
{
    RewardModelTest rewardModel;

    rewardModel.stop();
    const QTimer& resultAnimTimer    = rewardModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardModel.getDestroyTimer();

    EXPECT_EQ(resultAnimTimer.isActive(),    false);
    EXPECT_EQ(resultDestroyTimer.isActive(), false);
}

TEST_F(RewardModelTestsClass, Animation_AnimationFrameIdxIs0CheckIfWillBeIncreased_IsOne)
{
    QImage dumpImage;
    RewardModelTest rewardModel;
    rewardModel.setImage(&dumpImage);

    rewardModel.animation();
    int resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 1);
}

TEST_F(RewardModelTestsClass, Animation_AnimationFrameIdxIsMaxCheckIfWillBeResetTo0_IsZero)
{
    QImage dumpImage;
    RewardModelTest rewardModel;
    rewardModel.setImage(&dumpImage);
    rewardModel.setAnimationFrameIdx(def::maxAnimationFrameIdx);

    rewardModel.animation();
    int resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, 0);
}

TEST_F(RewardModelTestsClass, Animation_AnimationFrameIdxIsMaxMinusOneCheckIfWillBeSetToMax_IsEqual)
{
    QImage dumpImage;
    RewardModelTest rewardModel;
    rewardModel.setImage(&dumpImage);
    rewardModel.setAnimationFrameIdx(def::maxAnimationFrameIdx - 1);

    rewardModel.animation();
    int resultAnimFrameIdx = rewardModel.getAnimationFrameIdx();

    EXPECT_EQ(resultAnimFrameIdx, def::maxAnimationFrameIdx);
}

TEST_F(RewardModelTestsClass, Destroy_CheckCorrectWorking_IsZero)
{
    QGraphicsScene   scene;
    RewardModelTest* rewardModel = new RewardModelTest;
    scene.addItem(rewardModel);
    int resultShouldBeOne = scene.items().size();

    rewardModel->destroy();
    int resultSholudBeZero = scene.items().size();

    EXPECT_EQ(resultShouldBeOne,  1);
    EXPECT_EQ(resultSholudBeZero, 0);
}
