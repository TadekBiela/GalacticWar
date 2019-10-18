#include "scorecontroller.hpp"

ScoreController::ScoreController(ScoreModel *model,
                                 ScoreView  *view)
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

}

void ScoreController::maxPerLevelAchieved()
{
    emit maxScorePerLevelAchieved();
}
