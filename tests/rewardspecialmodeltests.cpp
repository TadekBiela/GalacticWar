#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
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
    RewardSpecialModelTest(special_type type)
                            : RewardSpecialModel(type) {}
    virtual ~RewardSpecialModelTest() {}

    special_type  getType()              const { return m_type; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }
    void          setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
};

class RewardSpecialModelTestsClass : public testing::Test
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

TEST_F(RewardSpecialModelTestsClass, RewardSpecialModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardSpecialModelTest rewardSpecialModel(special_type::health);
    special_type  resultType         = rewardSpecialModel.getType();
    int           resultAnimFrameIdx = rewardSpecialModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardSpecialModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardSpecialModel.getDestroyTimer();

    EXPECT_EQ(resultType,                          special_type::health);
    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
}

TEST_F(RewardSpecialModelTestsClass, Collect_CheckIfWillBeSendSignalWithCorrectType_IsEqual)
{
    qRegisterMetaType<special_type>();
    QGraphicsScene          scene;
    RewardSpecialModelTest* rewardSpecialModel = new RewardSpecialModelTest(special_type::weaponYellow);
    scene.addItem(rewardSpecialModel);
    QSignalSpy signalCollect(rewardSpecialModel, &RewardSpecialModelTest::collected);
    signalCollect.wait(utdef::minSignalTimeDelay);

    rewardSpecialModel->collect();
    int             resultSignalCollectCount = signalCollect.count();
    QList<QVariant> resultSignalCollect      = signalCollect.takeFirst();
    special_type    resultType               = qvariant_cast<special_type>(resultSignalCollect.at(0));

    EXPECT_EQ(resultSignalCollectCount, 1);
    EXPECT_EQ(resultType,               special_type::weaponYellow);
}
