#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/generalview.hpp"
#include "../app/scorecontroller.hpp"
#include "../app/scoremodel.hpp"
#include <QSignalSpy>

using namespace testing;

class ScoreControllerTest : public ScoreController
{
public:
    ScoreControllerTest(QWidget* displayWidget)
                         : ScoreController(displayWidget)
    {
        create();
    }
    virtual ~ScoreControllerTest()
    {
        destroy();
    }
    void setGenerator(IRandomGenerator* generator)
    {
        delete m_generator;
        m_generator = generator;
    }
};

class ScoreControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
    }
};

TEST_F(ScoreControllerTestsClass, AddScorePointsBasedOnCoinType_CurrnetScoreIs0BronzeCoinAdded10Points_ShouldNotSendSignalMaxScorePerLevelAchieved)
{
    QWidget displayWidget;
    ScoreControllerTest scoreController(&displayWidget);
    RandomGeneratorStub* generatorStub = new RandomGeneratorStub;
    ON_CALL(*generatorStub, bounded).WillByDefault(Return(10));
    scoreController.setGenerator(generatorStub);
    QSignalSpy signalMaxScore(&scoreController, &ScoreControllerTest::maxScorePerLevelAchieved);
    signalMaxScore.wait(utdef::minSignalTimeDelay);

    scoreController.addScorePointsBasedOnCoinType(coin_type::bronze);
    int resultSignalMaxScore = signalMaxScore.count();

    EXPECT_EQ(0, resultSignalMaxScore);
}

TEST_F(ScoreControllerTestsClass, AddScorePointsBasedOnCoinType_CurrnetScoreIs0GoldCoinAdded10000Points_ShouldSendSignalMaxScorePerLevelAchieved)
{
    QWidget displayWidget;
    ScoreControllerTest scoreController(&displayWidget);
    RandomGeneratorStub* generatorStub = new RandomGeneratorStub;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(10000));
    scoreController.setGenerator(generatorStub);
    QSignalSpy signalMaxScore(&scoreController, &ScoreControllerTest::maxScorePerLevelAchieved);
    signalMaxScore.wait(utdef::minSignalTimeDelay);

    scoreController.addScorePointsBasedOnCoinType(coin_type::bronze);
    int resultSignalMaxScore = signalMaxScore.count();

    EXPECT_EQ(1, resultSignalMaxScore);
}
