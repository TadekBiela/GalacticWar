
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


#include "enemymodeltype4.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>


EnemyModelType4::EnemyModelType4(
    QPointF position
) :
    EnemyModel(
        def::enemy4Level,
        def::enemy4MaxHealthPoints,
        def::enemy4BaseDamage,
        def::enemy4MoveTimeDelay,
        def::enemy4FireTimeDelay
    ),
    m_jumpMoveTimeDelay(def::enemy4JumpTimeDelay),
    m_isJumpMove(false)
{
    if(position.x() <= def::halfSceneWidth) {
        m_jumpSide = enemy_jump_side::left;
    }
    else {
        m_jumpSide = enemy_jump_side::right;
    }

    m_direction = def::down;
    setRotation(m_direction);

    setCenterPosition(position);
}

EnemyModelType4::~EnemyModelType4() {

}

void EnemyModelType4::fire() {
    QPointF position = getCenterPosition();
    position.setY(position.y() + def::enemy4BulletYCoordinateOffsetInPx);
    BulletModel* bullet = new BulletModel(
        "bullet_enemy4",
        game_object_type::enemy_bullet,
        position,
        m_damage,
        def::down,
        def::enemy4BulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType4::move() {
    if(m_jumpMoveTimeDelay <= 0) {
        m_jumpMoveTimeDelay = def::enemy4JumpTimeDelay;
        m_isJumpMove = !m_isJumpMove;

        if(m_isJumpMove) {
            if(enemy_jump_side::right == m_jumpSide) {
                m_jumpSide = enemy_jump_side::left;
                m_animationFrameYIdx = 1;
            }
            else {
                m_jumpSide = enemy_jump_side::right;
                m_animationFrameYIdx = 2;
            }

            m_fireTimer.setInterval(def::enemy4SpeedupFireTimeDelay);
        }
        else {
            m_animationFrameYIdx = 0;
            m_fireTimer.setInterval(def::enemy4FireTimeDelay);
        }
    }

    if(m_isJumpMove) {
        jumpMove();
    }
    else {
        setPos(
            moveForward(
                pos(),
                m_direction,
                def::enemy4MoveYCoordinateOffset
            )
        );
    }

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    checkCollisions();

    m_jumpMoveTimeDelay--;
}

void EnemyModelType4::jumpMove() {
    QPointF currentPosition = getCenterPosition();
    if(enemy_jump_side::right == m_jumpSide) {
        currentPosition.setX(currentPosition.x() + def::enemy4JumpMoveOffsetInPx);
    }
    else {
        currentPosition.setX(currentPosition.x() - def::enemy4JumpMoveOffsetInPx);
    }
    currentPosition.setY(currentPosition.y() + 1);
    setCenterPosition(currentPosition);
}

