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

int ScoreModel::getCurrentScore() const
{
    return m_currentScore;
}

int ScoreModel::getCurrentScoreInPercent() const
{
    return m_currentScore * 100 / getCurrentTreshold();
}

int ScoreModel::getCurrentTreshold() const
{
    return s_scoreTresholds[m_currentTresholdIdx];
}

int ScoreModel::getTotalScore() const
{
    return m_totalScore;
}

Score_Per_Level ScoreModel::add(int scorePoints)
{
    m_currentScore += scorePoints;
    m_totalScore   += scorePoints;
    int currentTreshold = getCurrentTreshold();

    if((m_currentScore >= currentTreshold) &&
       (m_currentTresholdIdx < def::maxNumOfLevel - 1))
    {
        m_currentScore -= currentTreshold;
        m_currentTresholdIdx++;
        return Score_Per_Level_Next;
    }
    return Score_Per_Level_Current;
}
