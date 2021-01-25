
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


#ifndef ENEMYTURRETTRIPLECANNON_HPP
#define ENEMYTURRETTRIPLECANNON_HPP

#include "definitions.hpp"
#include "enemyturret.hpp"
#include <QGraphicsItem>
#include <QPointF>

class EnemyTurretTripleCannon : public EnemyTurret
{
    Q_OBJECT
public:
    EnemyTurretTripleCannon(
        QGraphicsItem* parent,
        QPointF position,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection
    );
    virtual ~EnemyTurretTripleCannon();

protected slots:
    void fire();

protected:
    static const int s_fireCannonOffsets[def::enemyTurretTripleCannonMaxFireCannonOffsets];
    int m_currentFireCannonIdx;
};

#endif // ENEMYTURRETTRIPLECANNON_HPP
