#include "scorecontroller.hpp"

ScoreController::ScoreController(ScoreModel *model,
                                 ScoreView  *view,
                                 IRandomGenerator* generator)
                                  : m_generator(generator)
{
    connect(this,  SIGNAL(get()),                 model, SLOT(get()));
    connect(this,  SIGNAL(addPoints(int)),        model, SLOT(addPoints(int)));
    connect(model, SIGNAL(update(int)),           this,  SLOT(update(int)));
    connect(model, SIGNAL(maxPerLevelAchieved()), this, SLOT(maxPerLevelAchieved()));
    connect(model, SIGNAL(updateView(int)),       view, SLOT(update(int)));
}

ScoreController::~ScoreController()
{

}

void ScoreController::getScore()
{
    emit get();
}

void ScoreController::update(int score)
{
    emit updateScore(score);
}

void ScoreController::addScorePoints(coin_type coin)
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
    emit addPoints(points);
}

void ScoreController::maxPerLevelAchieved()
{
    emit maxScorePerLevelAchieved();
}
