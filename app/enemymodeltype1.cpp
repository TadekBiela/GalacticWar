
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


#include "enemymodeltype1.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType1::EnemyModelType1(
    QPointF position,
    IRandomGenerator* generator
) :
    EnemyModel(
        def::enemy1Level,
        def::enemy1MaxHealthPoints,
        def::enemy1BaseDamage,
        def::enemy1MoveTimeDelay,
        def::enemy1FireTimeDelay
    )
{
    const int randomGeneratedResult = generator->bounded(0, 1);
    if(0 == randomGeneratedResult) {
        m_direction = def::down;
        m_animationFrameYIdx = 0;
    }
    else if(position.x() <= def::halfSceneWidth) {
        m_direction = def::enemy1RightMoveDirection;
        m_animationFrameYIdx = 1;
    }
    else {
        m_direction = def::enemy1LeftMoveDirection;
        m_animationFrameYIdx = 2;
    }

    setRotation(m_direction);

    setCenterPosition(position);
}

EnemyModelType1::~EnemyModelType1() {

}

void EnemyModelType1::fire() {
    QPointF bulletPosition = moveForward(
        getCenterPosition(),
        m_direction,
        def::enemy1FireBulletOffset
    );
    BulletModel* bullet = new BulletModel(
        "bullet_enemy",
        game_object_type::enemy_bullet,
        bulletPosition,
        m_damage,
        m_direction,
        def::defaultBulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType1::move() {
    setPos(moveForward(pos(), m_direction));

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    checkCollisions();
}
