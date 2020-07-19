#include "scorecontroller.hpp"
#include "randomgenerator.hpp"

ScoreController::ScoreController(QWidget* displayWidget)
                                  : m_displayWidget(displayWidget),
                                    m_generator(new RandomGenerator()),
                                    m_model(nullptr),
                                    m_view(nullptr)
{

}

ScoreController::~ScoreController()
{
    delete m_generator;
    if(m_model)
    {
        delete m_model;
    }
    if(m_view)
    {
        delete m_view;
    }
}

void ScoreController::create()
{
    m_model = new ScoreModel();
    m_view  = new BarView(m_displayWidget,
                          "scoreBar",
                          def::darkYellowHex);
    m_view->setPosition(def::scoreGraphicsPositionX,
                        def::scoreGraphicsPositionY);
}

void ScoreController::destroy()
{
    delete m_model;
    delete m_view;
}

void ScoreController::show()
{
    m_view->show();
}

void ScoreController::hide()
{
    m_view->hide();
}

void ScoreController::addScorePointsBasedOnCoinType(coin_type coin)
{
    int points = 0;
    switch (coin)
    {
        case bronze:
            points = m_generator->bounded(def::minPointsForBronzeCoin,
                                          def::maxPointsForBronzeCoin);
            break;
        case silver:
            points = m_generator->bounded(def::minPointsForSilverCoin,
                                          def::maxPointsForSilverCoin);
            break;
        case gold:
            points = m_generator->bounded(def::minPointsForGoldCoin,
                                          def::maxPointsForGoldCoin);
            break;
    }
    Score_Per_Level status = m_model->add(points);
    if(Score_Per_Level_Next == status)
    {
        emit maxScorePerLevelAchieved();
    }
    m_view->set(m_model->getCurrentScoreInPercent());
}

void ScoreController::emitTotalScoreAndDestroy()
{
    emit totalScore(m_model->getTotalScore());
    destroy();
}
