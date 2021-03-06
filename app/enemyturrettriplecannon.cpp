
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


#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "enemyturrettriplecannon.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

const int EnemyTurretTripleCannon::s_fireCannonOffsets[def::enemyTurretTripleCannonMaxFireCannonOffsets] = {
    7,
    0,
    -7
};

EnemyTurretTripleCannon::EnemyTurretTripleCannon(
    QGraphicsItem* parent,
    QPointF position,
    int startRotationDegree,
    enemy_turret_rotate_direction rotationDirection
) :
    EnemyTurret(
        parent,
        "enemy_turret2",
        position,
        def::enemyTurretTripleCannonDamage,
        def::enemyTurretTripleCannonFireTimeDelay,
        startRotationDegree,
        rotationDirection,
        def::enemyTurretTripleCannonRotateTimeDelay
    ),
    m_currentFireCannonIdx(0)
{

}

EnemyTurretTripleCannon::~EnemyTurretTripleCannon() {

}

void EnemyTurretTripleCannon::fire() {
    const int bulletMoveDirection = (m_rotationDegree + parentItem()->rotation());
    const int pixmapHalfWidth = (pixmap().width() / 2);
    const int bulletPositionOffsetVector = (bulletMoveDirection + 90) % def::maxDegree;

    QPointF fireCannonPosition = moveForward(
        scenePos(),
        bulletPositionOffsetVector,
        (pixmapHalfWidth - s_fireCannonOffsets[m_currentFireCannonIdx])
    );
    BulletModel* bullet = new BulletModel(
        "bullet_enemy9",
        game_object_type::enemy_bullet,
        fireCannonPosition,
        m_damage,
        bulletMoveDirection,
        def::defaultBulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);

    m_currentFireCannonIdx++;
    m_currentFireCannonIdx %= def::enemyTurretTripleCannonMaxFireCannonOffsets;
}

