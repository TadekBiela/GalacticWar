
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


#ifndef SCORECONTROLLER_HPP
#define SCORECONTROLLER_HPP

#include "barview.hpp"
#include "controlplane.hpp"
#include "irandomgenerator.hpp"
#include "scoremodel.hpp"
#include "rewardtypes.hpp"
#include <QObject>

class ScoreController : public QObject
{
    Q_OBJECT
public:
    ScoreController(QWidget*      displayWidget,
                    ControlPlane* controller);
    virtual ~ScoreController();

signals:
    void maxScorePerLevelAchieved();
    void totalScore(int total);

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void addScorePointsBasedOnCoinType(coin_type coin);
    void emitTotalScoreAndDestroy();

protected:
    QWidget*          m_displayWidget;
    ControlPlane*     m_controller;
    IRandomGenerator* m_generator;
    ScoreModel*       m_model;
    BarView*          m_view;
};

#endif // SCORECONTROLLER_HPP
