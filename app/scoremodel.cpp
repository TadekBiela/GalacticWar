#include "scoremodel.hpp"

const int ScoreModel::s_scoreTresholds[def::maxNumOfLevel] =
{
     1000,  3000,   7000,  15000,  30000,
    55000, 95000, 150000, 210000, 300000
};

ScoreModel::ScoreModel()
{

}

void ScoreModel::addScorePoints(int newValue)
{

}
