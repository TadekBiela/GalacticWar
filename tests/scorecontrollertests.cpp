#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/scorecontroller.hpp"
#include "../app/scoremodel.hpp"
#include "../app/scoreview.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(coin_type)

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

TEST_F(ScoreControllerTestsClass, GetScore_CheckIfWillSendGetSignal_IsEqual)
{
    ScoreModel*         model = new ScoreModel;
    ScoreView*          view  = new ScoreView;
    ScoreControllerTest scoreController(model, view);
    QSignalSpy signalUpdate(&scoreController, &ScoreControllerTest::get);
    signalUpdate.wait(utdef::minSignalTimeDelay);

    scoreController.getScore();
    int resultSignalUpdateCount = signalUpdate.count();

    EXPECT_EQ(resultSignalUpdateCount, 1);
    delete model;
    delete view;
}
