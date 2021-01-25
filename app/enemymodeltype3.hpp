
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


#ifndef ENEMYMODELTYPE3_HPP
#define ENEMYMODELTYPE3_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_fire_side {
    left_cannon,
    right_cannon
};

class EnemyModelType3 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType3(
        QPointF position
    );
    virtual ~EnemyModelType3();

public slots:
    void fire();
    void move();

protected:
    enemy_fire_side m_fireSide;
    enemy_rotation_direction m_moveRotationSide;
    int m_moveSlowFactor;
    int m_rotateMinBorder;
    int m_rotateMaxBorder;
};

#endif // ENEMYMODELTYPE3_HPP
