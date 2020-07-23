#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/definitions.hpp"
#include "../app/rewardcontroller.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QSignalSpy>

using namespace testing;

Q_DECLARE_METATYPE(GameObject*)
Q_DECLARE_METATYPE(coin_type)
Q_DECLARE_METATYPE(special_type)

class RewardControllerTest : public RewardController
{
public:
    RewardControllerTest(GameplayView* view)
        : RewardController(view) {}
    virtual ~RewardControllerTest() {}
    void setGenerator(IRandomGenerator* generator)
    {
        delete m_generator;
        m_generator = generator;
    }
};

class RewardControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
        ImageStorageStub* imageStorageStub = dynamic_cast<ImageStorageStub*>(g_imageStorage);
        imageStorageStub->setDummyImageSize(def::animationSmallFrameWight,
                                            def::animationSmallFrameWight);
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

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier1_OnlyOneBronzeCoinShouldBeSpawned)
{
    qRegisterMetaType<GameObject*>();
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    EXPECT_CALL(*generator, bounded(_,_))
            .WillOnce(Return(1))    //num of coins
            .WillOnce(Return(0))    //type for #1 coin
            .WillOnce(Return(5))    //offsets to position for #1 coin
            .WillOnce(Return(-10))
            .WillOnce(Return(1));   //specials probability (should be false)
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    RewardControllerTest rewardController(&view);
    rewardController.setGenerator(generator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 1);
    int  resultSignalCoinCount = signalReward.count();
    auto resultCoinReward      = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.takeFirst().at(0)));

    EXPECT_EQ(1, resultSignalCoinCount);
    EXPECT_FLOAT_EQ(39, resultCoinReward->pos().x());
    EXPECT_FLOAT_EQ(24, resultCoinReward->pos().y());
    EXPECT_EQ(coin_type::bronze, resultCoinReward->getType());
}

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier2_CoinsOneBronzeAndOneSilverShouldBeSpawned)
{
    qRegisterMetaType<GameObject*>();
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    EXPECT_CALL(*generator, bounded(_,_))
            .WillOnce(Return(2))    //num of coins
            .WillOnce(Return(7))    //type for #1 coin
            .WillOnce(Return(-5))   //offsets to position for #1 coin
            .WillOnce(Return(0))
            .WillOnce(Return(8))    //type for #2 coin
            .WillOnce(Return(5))    //offsets to position for #2 coin
            .WillOnce(Return(8))
            .WillOnce(Return(3));   //specials probability (should be false)
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    RewardControllerTest rewardController(&view);
    rewardController.setGenerator(generator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 2);
    int  resultSignalsCount = signalReward.count();
    auto resultCoinReward1  = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.at(0).at(0)));
    auto resultCoinReward2  = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.at(1).at(0)));

    EXPECT_EQ(2 ,resultSignalsCount);
    EXPECT_FLOAT_EQ(29, resultCoinReward1->pos().x());
    EXPECT_FLOAT_EQ(34, resultCoinReward1->pos().y());
    EXPECT_EQ(coin_type::bronze, resultCoinReward1->getType());
    EXPECT_FLOAT_EQ(39, resultCoinReward2->pos().x());
    EXPECT_FLOAT_EQ(42, resultCoinReward2->pos().y());
    EXPECT_EQ(coin_type::silver, resultCoinReward2->getType());
}

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier3_AllTypesCoinsAndSpecialRewardsShouldBeSpawned)
{
    qRegisterMetaType<GameObject*>();
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    EXPECT_CALL(*generator, bounded(_,_))
            .WillOnce(Return(3))    //num of coins
            .WillOnce(Return(1))    //#1
            .WillOnce(Return(5))
            .WillOnce(Return(5))
            .WillOnce(Return(6))    //#2
            .WillOnce(Return(-10))
            .WillOnce(Return(0))
            .WillOnce(Return(9))    //#3
            .WillOnce(Return(-2))
            .WillOnce(Return(-4))
            .WillOnce(Return(1))    //specials probability (should be true)
            .WillOnce(Return(1));   //type for #1 special
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    RewardControllerTest rewardController(&view);
    rewardController.setGenerator(generator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 3);
    int  resultSignalsCount  = signalReward.count();
    auto resultCoinReward1   = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.at(0).at(0)));
    auto resultCoinReward2   = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.at(1).at(0)));
    auto resultCoinReward3   = dynamic_cast<RewardCoinModel*>(qvariant_cast<GameObject*>(signalReward.at(2).at(0)));
    auto resultSpecialReward = dynamic_cast<RewardSpecialModel*>(qvariant_cast<GameObject*>(signalReward.at(3).at(0)));

    EXPECT_EQ(4, resultSignalsCount);
    EXPECT_FLOAT_EQ(39, resultCoinReward1->pos().x());
    EXPECT_FLOAT_EQ(39, resultCoinReward1->pos().y());
    EXPECT_EQ(coin_type::bronze, resultCoinReward1->getType());
    EXPECT_FLOAT_EQ(24, resultCoinReward2->pos().x());
    EXPECT_FLOAT_EQ(34, resultCoinReward2->pos().y());
    EXPECT_EQ(coin_type::silver, resultCoinReward2->getType());
    EXPECT_FLOAT_EQ(32, resultCoinReward3->pos().x());
    EXPECT_FLOAT_EQ(30, resultCoinReward3->pos().y());
    EXPECT_EQ(coin_type::gold, resultCoinReward3->getType());
    EXPECT_FLOAT_EQ(34, resultSpecialReward->pos().x());
    EXPECT_FLOAT_EQ(34, resultSpecialReward->pos().y());
    EXPECT_EQ(special_type::health, resultSpecialReward->getType());
}

TEST_F(RewardControllerTestsClass, CoinCollected_BronzeCollected_ShouldSendRewardCoinCollectedSignalWithCorrectType)
{
    qRegisterMetaType<coin_type>();
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    RewardControllerTest rewardController(&view);
    QSignalSpy signalCoin(&rewardController, &RewardControllerTest::rewardCoinCollected);
    signalCoin.wait(utdef::minSignalTimeDelay);

    rewardController.coinCollected(coin_type::bronze);
    int  resultSignalCoinCount = signalCoin.count();
    auto resultCoinType        = qvariant_cast<coin_type>(signalCoin.takeFirst().at(0));

    EXPECT_EQ(1,                 resultSignalCoinCount);
    EXPECT_EQ(coin_type::bronze, resultCoinType);
}

TEST_F(RewardControllerTestsClass, SpecialCollected_WeaponRedCollected_ShouldSendRewardSpecialCollectedSignalWithCorrectType)
{
    qRegisterMetaType<special_type>();
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    RewardControllerTest rewardController(&view);
    QSignalSpy signalSpecial(&rewardController, &RewardControllerTest::rewardSpecialCollected);
    signalSpecial.wait(utdef::minSignalTimeDelay);

    rewardController.specialCollected(special_type::weaponRed);
    int  resultSignalSpecialCount = signalSpecial.count();
    auto resultSpecialType        = qvariant_cast<special_type>(signalSpecial.takeFirst().at(0));

    EXPECT_EQ(1,                       resultSignalSpecialCount);
    EXPECT_EQ(special_type::weaponRed, resultSpecialType);
}
