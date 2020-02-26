#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/generalview.hpp"
#include "../app/rewardcontroller.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(coin_type)
Q_DECLARE_METATYPE(special_type)

class RewardControllerTest : public RewardController
{
public:
    RewardControllerTest(GeneralView*      view,
                         IRandomGenerator* generator)
                          : RewardController(view,
                                             generator) {}
    virtual ~RewardControllerTest() {}
};

class RewardControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(def::animationSmallFrameWight, def::animationSmallFrameWight);
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier1OnlyOneBronzeCoinShouldBeSpawned_IsEqual)
{
    int sequance[] = { 1,      //coins
                       0,      //type for #1 coin
                       5, -10, //offsets to position for #1 coin
                       1 };    //specials probability (should be false)
    RandomSequanceGeneratorStub* randomGenerator = new RandomSequanceGeneratorStub(5, sequance);
    GeneralView* view = new GeneralView;
    RewardControllerTest rewardController(view, randomGenerator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 1);
    int  resultSignalCoinCount = signalReward.count();
    auto resultCoinReward      = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.takeFirst().at(0)));

    EXPECT_EQ(resultSignalCoinCount,              1);
    EXPECT_FLOAT_EQ(resultCoinReward->pos().x(), 39);
    EXPECT_FLOAT_EQ(resultCoinReward->pos().y(), 24);
    EXPECT_EQ(resultCoinReward->getType(),       coin_type::bronze);
    delete view;
    delete randomGenerator;
}

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier2CoinsOneBronzeAndOneSilverShouldBeSpawned_IsEqual)
{
    int sequance[] = { 2,     //coins
                       7,     //type for #1 coin
                       -5, 0, //offsets to position for #1 coin
                       8,     //type for #2 coin
                       5, 8,  //offsets to position for #2 coin
                       3 };   //specials probability (should be false)
    RandomSequanceGeneratorStub* randomGenerator = new RandomSequanceGeneratorStub(8, sequance);
    GeneralView* view = new GeneralView;
    RewardControllerTest rewardController(view, randomGenerator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 2);
    int  resultSignalsCount = signalReward.count();
    auto resultCoinReward1  = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(0).at(0)));
    auto resultCoinReward2  = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(1).at(0)));

    EXPECT_EQ(resultSignalsCount,                  2);
    EXPECT_FLOAT_EQ(resultCoinReward1->pos().x(), 29);
    EXPECT_FLOAT_EQ(resultCoinReward1->pos().y(), 34);
    EXPECT_EQ(resultCoinReward1->getType(),       coin_type::bronze);
    EXPECT_FLOAT_EQ(resultCoinReward2->pos().x(), 39);
    EXPECT_FLOAT_EQ(resultCoinReward2->pos().y(), 42);
    EXPECT_EQ(resultCoinReward2->getType(),       coin_type::silver);
    delete view;
    delete randomGenerator;
}

TEST_F(RewardControllerTestsClass, SpawnRewards_Tier3AllTypesCoinsAndSpecialRewardsShouldBeSpawned_IsEqual)
{
    int sequance[] = { 3,      //coins
                       1,      //#1
                       5, 5,
                       6,      //#2
                       -10, 0,
                       9,      //#3
                       -2, -4,
                       1,      //specials probability (should be true)
                       1 };    //type for #1 special
    RandomSequanceGeneratorStub* randomGenerator = new RandomSequanceGeneratorStub(12, sequance);
    GeneralView* view = new GeneralView;
    RewardControllerTest rewardController(view, randomGenerator);
    QSignalSpy signalReward(&rewardController, &RewardControllerTest::addRewardToScene);
    signalReward.wait(utdef::minSignalTimeDelay);

    rewardController.spawnRewards(QPointF(50, 50), 3);
    int  resultSignalsCount  = signalReward.count();
    auto resultCoinReward1   = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(0).at(0)));
    auto resultCoinReward2   = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(1).at(0)));
    auto resultCoinReward3   = dynamic_cast<RewardCoinModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(2).at(0)));
    auto resultSpecialReward = dynamic_cast<RewardSpecialModel*>(qvariant_cast<QGraphicsItem*>(signalReward.at(3).at(0)));

    EXPECT_EQ(resultSignalsCount,                    4);
    EXPECT_FLOAT_EQ(resultCoinReward1->pos().x(),   39);
    EXPECT_FLOAT_EQ(resultCoinReward1->pos().y(),   39);
    EXPECT_EQ(resultCoinReward1->getType(),         coin_type::bronze);
    EXPECT_FLOAT_EQ(resultCoinReward2->pos().x(),   24);
    EXPECT_FLOAT_EQ(resultCoinReward2->pos().y(),   34);
    EXPECT_EQ(resultCoinReward2->getType(),         coin_type::silver);
    EXPECT_FLOAT_EQ(resultCoinReward3->pos().x(),   32);
    EXPECT_FLOAT_EQ(resultCoinReward3->pos().y(),   30);
    EXPECT_EQ(resultCoinReward3->getType(),         coin_type::gold);
    EXPECT_FLOAT_EQ(resultSpecialReward->pos().x(), 34);
    EXPECT_FLOAT_EQ(resultSpecialReward->pos().y(), 34);
    EXPECT_EQ(resultSpecialReward->getType(),       special_type::health);
    delete view;
    delete randomGenerator;
}

TEST_F(RewardControllerTestsClass, CoinCollected_BronzeCollectedCheckIfWillSendRewardCoinCollectedSignalWithCorrectType_IsEqual)
{
    qRegisterMetaType<coin_type>();
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    GeneralView*         view            = new GeneralView;
    RewardControllerTest rewardController(view, randomGenerator);
    QSignalSpy signalCoin(&rewardController, &RewardControllerTest::rewardCoinCollected);
    signalCoin.wait(utdef::minSignalTimeDelay);

    rewardController.coinCollected(coin_type::bronze);
    int  resultSignalCoinCount = signalCoin.count();
    auto resultCoinType        = qvariant_cast<coin_type>(signalCoin.takeFirst().at(0));

    EXPECT_EQ(resultSignalCoinCount, 1);
    EXPECT_EQ(resultCoinType,        coin_type::bronze);
    delete view;
    delete randomGenerator;
}

TEST_F(RewardControllerTestsClass, SpecialCollected_WeaponRedCollectedCheckIfWillSendRewardSpecialCollectedSignalWithCorrectType_IsEqual)
{
    qRegisterMetaType<special_type>();
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    GeneralView*         view            = new GeneralView;
    RewardControllerTest rewardController(view, randomGenerator);
    QSignalSpy signalSpecial(&rewardController, &RewardControllerTest::rewardSpecialCollected);
    signalSpecial.wait(utdef::minSignalTimeDelay);

    rewardController.specialCollected(special_type::weaponRed);
    int  resultSignalSpecialCount = signalSpecial.count();
    auto resultSpecialType        = qvariant_cast<special_type>(signalSpecial.takeFirst().at(0));

    EXPECT_EQ(resultSignalSpecialCount, 1);
    EXPECT_EQ(resultSpecialType,        special_type::weaponRed);
    delete view;
    delete randomGenerator;
}
