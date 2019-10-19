#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
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
                         IRandomGenerator* generator) :
                         RewardController(view,
                                          generator) {}
};

class RewardControllerTestsClass : public testing::Test
{
};

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
