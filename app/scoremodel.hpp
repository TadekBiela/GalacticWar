#ifndef SCOREMODEL_HPP
#define SCOREMODEL_HPP

#include "definitions.hpp"

enum Score_Per_Level
{
    Score_Per_Level_Current = 0,
    Score_Per_Level_Next    = 1
};

class ScoreModel
{

public:
    ScoreModel();
    virtual ~ScoreModel();
    int getCurrentScore() const;
    int getCurrentScoreInPercent() const;
    int getCurrentTreshold() const;
    int getTotalScore() const;
    Score_Per_Level add(int scorePoints);

protected:
    int m_currentTresholdIdx;
    int m_currentScore;
    int m_totalScore;

    static const int s_scoreTresholds[def::maxNumOfLevel];
};

#endif // SCOREMODEL_HPP
