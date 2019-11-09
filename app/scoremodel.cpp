#include "scoremodel.hpp"

const int ScoreModel::s_scoreTresholds[def::maxNumOfLevel] =
{
     1000,  3000,   7000,  15000,  30000,
    55000, 95000, 150000, 210000, 300000
};

ScoreModel::ScoreModel()
                       : m_currentTresholdIdx(0),
                         m_currentScore(0),
                         m_totalScore(0)
{

}

ScoreModel::~ScoreModel()
{

}

void ScoreModel::reset()
{
    m_currentTresholdIdx = 0;
    m_currentScore       = 0;
    m_totalScore         = 0;

    addPoints(0);
}

void ScoreModel::get()
{
    emit update(m_totalScore);
}

void ScoreModel::addPoints(int points)
{
    m_currentScore += points;
    m_totalScore   += points;
    int currentTreshold = s_scoreTresholds[m_currentTresholdIdx];

    if(m_currentScore >= currentTreshold && m_currentTresholdIdx < def::maxNumOfLevel - 1)
    {
        m_currentScore -= currentTreshold;
        m_currentTresholdIdx++;
        currentTreshold = s_scoreTresholds[m_currentTresholdIdx];
        emit maxPerLevelAchieved();
    }
    int percentCurrScore = m_currentScore * 100 / currentTreshold;

    emit updateView(percentCurrScore);
}
