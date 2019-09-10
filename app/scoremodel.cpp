#include "scoremodel.hpp"

const int ScoreModel::s_scoreTresholds[def::maxNumOfLevel] =
{
    1000,  1500,  2500,  4000,  6000,
    8500, 12000, 15000, 20000, 30000
};

ScoreModel::ScoreModel()
{

}

void ScoreModel::addScorePoints(int newValue)
{

}
