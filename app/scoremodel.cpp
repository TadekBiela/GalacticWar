#include "scoremodel.hpp"

const int ScoreModel::s_scoreTresholds[def::maxNumOfLevel] =
{
     1000,  3000,   7000,  15000,  30000,
    55000, 95000, 150000, 210000, 300000
};

ScoreModel::ScoreModel() :
    m_currentTresholdIdx(0),
    m_totalScore(0)
{

}

void ScoreModel::addScorePoints(int newValue)
{

}
