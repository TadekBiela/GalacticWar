#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/scorecontroller.hpp"
#include "../app/scoremodel.hpp"
#include "../app/scoreview.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(coin_type)

class ScoreModelMock : public ScoreModel
{
public:
    void setScore(int score) { m_totalScore = score; }
    int getScore() const { return m_totalScore; }
};

class ScoreControllerTest : public ScoreController
{
public:
    ScoreControllerTest(ScoreModel* ScoreModel,
                        ScoreView*  ScoreView) :
                        ScoreController(ScoreModel,
                                        ScoreView) {}
};

class ScoreControllerTestsClass : public testing::Test
{
};

TEST_F(ScoreControllerTestsClass, GetScore_CheckIfWillSendNextScoreInModelSignalOneTime_IsEqual)
{
    ScoreModelMock* model = new ScoreModelMock;
    model->setScore(100);
    ScoreView* view  = new ScoreView;
    ScoreControllerTest scoreController(model, view);
    QSignalSpy signalUpdate(&scoreController, &ScoreControllerTest::updateScore);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreController.getScore();
    int resultSignalUpdateCount = signalUpdate.count();
    int resultScore             = signalUpdate.takeFirst().at(0).toInt();

    EXPECT_EQ(resultSignalUpdateCount, 1);
    EXPECT_EQ(resultScore,             100);
    delete model;
    delete view;
}
