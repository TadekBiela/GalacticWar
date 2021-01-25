
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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
