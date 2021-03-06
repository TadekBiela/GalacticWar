
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


#include "enemymodeltype3.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType3::EnemyModelType3(
    QPointF position
) :
    EnemyModel(
        def::enemy3Level,
        def::enemy3MaxHealthPoints,
        def::enemy3BaseDamage,
        def::enemy3MoveTimeDelay,
        def::enemy3FireTimeDelay
    ),
    m_fireSide(enemy_fire_side::right_cannon),
    m_moveSlowFactor(def::enemy3MoveSlowFactor)
{
    int positionSideOffset = def::animationFrameWidth;

    if(position.x() < def::halfSceneWidth) {
        setCenterPosition(positionSideOffset, position.y());
        m_moveRotationSide = enemy_rotation_direction::left;
        m_rotateMinBorder = def::enemy3RotateLeftSideMinBorder;
        m_rotateMaxBorder = def::enemy3RotateLeftSideMaxBorder;
    }
    else {
        setCenterPosition((def::sceneWidth - positionSideOffset), position.y());
        m_moveRotationSide = enemy_rotation_direction::right;
        m_rotateMinBorder = def::enemy3RotateRightSideMinBorder;
        m_rotateMaxBorder = def::enemy3RotateRightSideMaxBorder;
    }

    m_direction = def::down;
    setRotation(m_direction);
}

EnemyModelType3::~EnemyModelType3() {

}

void EnemyModelType3::fire() {
    int bulletPositionOffsetDirection = 0;;
    if(enemy_fire_side::left_cannon == m_fireSide) {
        m_fireSide = enemy_fire_side::right_cannon;
        bulletPositionOffsetDirection = m_direction + 90;
    }
    else {
        m_fireSide = enemy_fire_side::left_cannon;
        bulletPositionOffsetDirection = m_direction - 90;
    }

    QPointF enemyPosition = getCenterPosition();
    QPointF bulletPosition = moveForward(
        enemyPosition,
        bulletPositionOffsetDirection,
        def::enemy3FireSideOffset
    );

    BulletModel* bullet = new BulletModel(
        "bullet_enemy3",
        game_object_type::enemy_bullet,
        bulletPosition,
        m_damage,
        m_direction,
        def::enemy3BulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType3::move() {
    QPointF moveNextPosition = pos();
    moveNextPosition.setY(moveNextPosition.y() + m_moveSlowFactor);
    setPos(moveNextPosition);

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    if(def::enemy3MinMoveSlowFactor < m_moveSlowFactor) {
        m_moveSlowFactor--;
    }

    if(enemy_rotation_direction::left == m_moveRotationSide) {
        m_direction -= def::enemy3RotateAngle;
        if(m_direction <= m_rotateMinBorder) {
            m_moveRotationSide = enemy_rotation_direction::right;
            m_animationFrameYIdx = 1;
        }
    }
    else {
        m_direction += def::enemy3RotateAngle;
        if(m_rotateMaxBorder <= m_direction) {
            m_moveRotationSide = enemy_rotation_direction::left;
            m_animationFrameYIdx = 2;
        }
    }
    setRotation(m_direction);

    checkCollisions();
}
