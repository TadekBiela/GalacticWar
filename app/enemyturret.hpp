
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


#ifndef ENEMYTURRET_HPP
#define ENEMYTURRET_HPP

#include "gameobject.hpp"
#include <QPointF>
#include <QString>
#include <QTimer>

enum class enemy_turret_rotate_direction {
    left = -1,
    right = 1
};

class EnemyTurret : public GameObject
{
    Q_OBJECT
public:
    EnemyTurret(
        QGraphicsItem* parent,
        QString graphicsName,
        QPointF position,
        int damage,
        int fireTimeDelay,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection,
        int rotateTimeDelay
    );
    virtual ~EnemyTurret();

public slots:
    void start() override;
    void stop() override;

protected slots:
    virtual void fire() = 0;
    void rotate();

protected:
    int m_damage;
    QTimer m_fireTimer;
    enemy_turret_rotate_direction m_rotationDirection;
    int m_rotationDegree;
    int m_maxRotationDegree;
    QTimer m_rotateTimer;
};

#endif // ENEMYTURRET_HPP
