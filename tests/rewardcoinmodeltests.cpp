#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/definitions.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardtypes.hpp"
#include <QTimer>
#include <QGraphicsScene>
#include <QSignalSpy>

Q_DECLARE_METATYPE(coin_type)

class RewardCoinModelTest : public RewardCoinModel
{
public:
    RewardCoinModelTest(coin_type type)
                         : RewardCoinModel(type) {}
    virtual ~RewardCoinModelTest() {}

    coin_type     getType()              const { return m_type; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    const QTimer& getDestroyTimer()      const { return m_destroyTimer; }
    void          setAnimationFrameIdx(int idx) { m_animationFrameIdx = idx; }
};

class RewardCoinModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage       = new ImageStorageStub;
        g_soundStorage       = new SoundStorageStub;
        m_displayWidget      = new QWidget;
        g_animationPlaneView = new AnimationPlaneView(m_displayWidget);
    }
    void TearDown()
    {
        delete g_animationPlaneView;
        delete m_displayWidget;
        delete g_imageStorage;
        delete g_soundStorage;
    }

private:
    QWidget* m_displayWidget;
};

TEST_F(RewardCoinModelTestsClass, RewardCoinModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    RewardCoinModelTest rewardCoinModel(coin_type::bronze);
    coin_type     resultType         = rewardCoinModel.getType();
    int           resultAnimFrameIdx = rewardCoinModel.getAnimationFrameIdx();
    const QTimer& resultAnimTimer    = rewardCoinModel.getAnimationTimer();
    const QTimer& resultDestroyTimer = rewardCoinModel.getDestroyTimer();

    EXPECT_EQ(resultType,                          coin_type::bronze);
    EXPECT_EQ(resultAnimFrameIdx,                  0);
    EXPECT_EQ(resultAnimTimer.isActive(),          true);
    EXPECT_EQ(resultDestroyTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(),    def::animationFrameDuration);
    EXPECT_FLOAT_EQ(resultDestroyTimer.interval(), def::defaultRewardDestroyTimeDelay);
}

TEST_F(RewardCoinModelTestsClass, Collect_CheckIfWillBeSendSignalWithCorrectType_IsEqual)
{
    qRegisterMetaType<coin_type>();
    QGraphicsScene       scene;
    RewardCoinModelTest* rewardCoinModel = new RewardCoinModelTest(coin_type::silver);
    scene.addItem(rewardCoinModel);
    QSignalSpy signalCollect(rewardCoinModel, &RewardCoinModelTest::collected);
    signalCollect.wait(utdef::minSignalTimeDelay);

    rewardCoinModel->collect();
    int             resultSignalCollectCount = signalCollect.count();
    QList<QVariant> resultSignalCollect      = signalCollect.takeFirst();
    coin_type       resultType               = qvariant_cast<coin_type>(resultSignalCollect.at(0));

    EXPECT_EQ(resultSignalCollectCount, 1);
    EXPECT_EQ(resultType,               coin_type::silver);
}
