#include "scorecontroller.hpp"

ScoreController::ScoreController(ScoreModel *model,
                                 ScoreView  *view)
{
    connect(this,  SIGNAL(get()),       model, SLOT(get()));
    connect(model, SIGNAL(update(int)), this,  SLOT(update(int)));
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

void ScoreController::maxPerLevelAchived()
{

}
