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
    m_totalScore += newValue;
    int percentScoreLevel = 0;
    int currentTreshold   = s_scoreTresholds[m_currentTresholdIdx];

    if(m_totalScore >= currentTreshold && m_currentTresholdIdx < def::maxNumOfLevel - 1)
    {
        m_currentTresholdIdx++;
        int newTreshold = s_scoreTresholds[m_currentTresholdIdx];
        int totalScoreInCurrentLevel = newTreshold - currentTreshold;
        percentScoreLevel = ((m_totalScore - currentTreshold) * 100) /
                            (totalScoreInCurrentLevel);
        emit maxScorePerLevelAchieved();
    }
    else
    {
        percentScoreLevel = (m_totalScore * 100) /
                            (s_scoreTresholds[m_currentTresholdIdx]);
    }
    emit updateScoreView(percentScoreLevel);
}
