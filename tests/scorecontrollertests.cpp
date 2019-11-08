#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/definitions.hpp"
#include "../app/generalview.hpp"
#include "../app/scorecontroller.hpp"
#include "../app/scoremodel.hpp"
#include <QSignalSpy>

class ScoreControllerTest : public ScoreController
{
public:
    ScoreControllerTest(ScoreModel*       model,
                        GeneralView*      view,
                        IRandomGenerator* generator)
                         : ScoreController(model,
                                           view,
                                           generator) {}
    virtual ~ScoreControllerTest() {}
};

class ScoreControllerTestsClass : public testing::Test
{
};

TEST_F(ScoreControllerTestsClass, ResetScore_CheckIfWillSendGetSignal_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalReset(&scoreController, &ScoreControllerTest::reset);
    signalReset.wait(utdef::minSignalTimeDelay);

    scoreController.resetScore();
    int resultSignalUpdateCount = signalReset.count();

    EXPECT_EQ(resultSignalUpdateCount, 1);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, GetScore_CheckIfWillSendGetSignal_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalUpdate(&scoreController, &ScoreControllerTest::get);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreController.getScore();
    int resultSignalUpdateCount = signalUpdate.count();

    EXPECT_EQ(resultSignalUpdateCount, 1);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, Update_CheckIfWillSendUpdateScoreSignal_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalUpdate(&scoreController, &ScoreControllerTest::updateScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreController.update(200);
    int resultSignalUpdateCount = signalUpdate.count();
    int resultScore             = signalUpdate.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalUpdateCount, 1);
    EXPECT_EQ(resultScore,             200);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, AddScorePoints_ReceivedBronzeCoinCheckIfWillSendSignalWithCorrectValue_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(def::minPointsForBronzeCoin);
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalAdd(&scoreController, &ScoreControllerTest::addPoints);
    signalAdd.wait(utdef::minSignalTimeDelay);

    scoreController.addScorePoints(coin_type::bronze);
    int resultSignalAddCount = signalAdd.count();
    int resultPoints         = signalAdd.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalAddCount, 1);
    EXPECT_EQ(resultPoints,         def::minPointsForBronzeCoin);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, AddScorePoints_ReceivedSilverCoinCheckIfWillSendSignalWithCorrectValue_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(def::minPointsForSilverCoin);
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalAdd(&scoreController, &ScoreControllerTest::addPoints);
    signalAdd.wait(utdef::minSignalTimeDelay);

    scoreController.addScorePoints(coin_type::silver);
    int resultSignalAddCount = signalAdd.count();
    int resultPoints         = signalAdd.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalAddCount, 1);
    EXPECT_EQ(resultPoints,         def::minPointsForSilverCoin);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, AddScorePoints_ReceivedGoldCoinCheckIfWillSendSignalWithCorrectValue_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(def::minPointsForGoldCoin);
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalAdd(&scoreController, &ScoreControllerTest::addPoints);
    signalAdd.wait(utdef::minSignalTimeDelay);

    scoreController.addScorePoints(coin_type::gold);
    int resultSignalAddCount = signalAdd.count();
    int resultPoints         = signalAdd.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalAddCount, 1);
    EXPECT_EQ(resultPoints,         def::minPointsForGoldCoin);
    delete model;
    delete view;
    delete randomGenerator;
}

TEST_F(ScoreControllerTestsClass, MaxPerLevelAchieved_CheckIfWillSendMaxScorePerLevelAchievedSignal_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    ScoreModel*         model = new ScoreModel;
    GeneralView*        view  = new GeneralView;
    ScoreControllerTest scoreController(model, view, randomGenerator);
    QSignalSpy signalMax(&scoreController, &ScoreControllerTest::maxScorePerLevelAchieved);
    signalMax.wait(utdef::minSignalTimeDelay);

    scoreController.maxPerLevelAchieved();
    int resultSignalMaxCount = signalMax.count();

    EXPECT_EQ(resultSignalMaxCount, 1);
    delete model;
    delete view;
    delete randomGenerator;
}
