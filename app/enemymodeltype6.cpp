
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


#include "enemymodeltype6.hpp"
#include "enemyturretdoublecannon.hpp"
#include "enemyturrettriplecannon.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>
#include <cmath>

EnemyModelType6::EnemyModelType6(
    QPointF startPosition,
    IRandomGenerator* generator
) :
    EnemyModel(
        def::enemy6Level,
        def::enemy6MaxHealthPoints,
        def::enemy6BaseDamage,
        def::enemy6MoveTimeDelay,
        def::enemy6FireTimeDelay,
        def::enemy6AnimationFrameWidth,
        def::enemy6AnimationFrameHeight
    )
{
    int startXCoordinate = 0;
    m_rotationCounter = generator->bounded(
        def::enemy6MinRotationDegrees,
        def::enemy6MaxRotationDegrees
    );
    const int directionOffset = def::right - m_rotationCounter;
    if(startPosition.x() <= def::halfSceneWidth) {
        startXCoordinate = 0 - def::enemy6StartXCoordinateOffset;
        m_direction = def::right + directionOffset;
        m_rotationDirection = enemy_rotation_direction::right;
        m_frontTurret = new EnemyTurretDoubleCannon(
            this,
            getFrontTurretStartPosition(),
            def::enemyTurretDoubleCannonFrontStartDirection,
            enemy_turret_rotate_direction::right
        );
        m_middleTurret = new EnemyTurretTripleCannon(
            this,
            getMiddleTurretStartPosition(),
            def::enemyTurretTripleCannonMiddleStartDirection,
            enemy_turret_rotate_direction::right
        );
        m_backTurret = new EnemyTurretDoubleCannon(
            this,
            getBackTurretStartPosition(),
            def::enemyTurretDoubleCannonBackStartDirection,
            enemy_turret_rotate_direction::left
        );
    }
    else {
        startXCoordinate = def::sceneWidth + def::enemy6StartXCoordinateOffset;
        m_direction = def::left - directionOffset;
        m_rotationDirection = enemy_rotation_direction::left;
        m_frontTurret = new EnemyTurretDoubleCannon(
            this,
            getFrontTurretStartPosition(),
            def::enemyTurretDoubleCannonFrontStartDirection,
            enemy_turret_rotate_direction::left
        );
        m_middleTurret = new EnemyTurretTripleCannon(
            this,
            getMiddleTurretStartPosition(),
            def::enemyTurretTripleCannonMiddleStartDirection,
            enemy_turret_rotate_direction::left
        );
        m_backTurret = new EnemyTurretDoubleCannon(
            this,
            getBackTurretStartPosition(),
            def::enemyTurretDoubleCannonBackStartDirection,
            enemy_turret_rotate_direction::right
        );
    }

    setRotation(m_direction);

    int startYCoordinate = generator->bounded(
        def::enemy6MinStartYCoordinate,
        def::enemy6MaxStartYCoordinate
    );
    startPosition.setX(startXCoordinate);
    startPosition.setY(startYCoordinate);
    setCenterPosition(startPosition);

    m_rotationTimeDelay = generator->bounded(
        def::enemy6MinRotationTimeDelay,
        def::enemy6MaxRotationTimeDelay
    );
}

EnemyModelType6::~EnemyModelType6() {
    delete m_frontTurret;
    m_frontTurret = nullptr;
}

void EnemyModelType6::start() {
    EnemyModel::start();
    m_frontTurret->start();
    m_middleTurret->start();
    m_backTurret->start();
}

void EnemyModelType6::stop() {
    EnemyModel::stop();
    m_frontTurret->stop();
    m_middleTurret->stop();
    m_backTurret->stop();
}

void EnemyModelType6::fire() {

}

void EnemyModelType6::move() {
    const int movePositionOffset = 2;
    setPos(moveForward(
        pos(),
        m_direction,
        movePositionOffset
    ));

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    checkCollisions();

    m_rotationTimeDelay--;
    if((m_rotationTimeDelay <= 0) && (0 < m_rotationCounter)) {
        m_rotationTimeDelay = 0;
        rotate();
    }
}

void EnemyModelType6::rotate() {
    m_rotationCounter--;

    if(enemy_rotation_direction::right == m_rotationDirection) {
        m_direction++;
    }
    else {
        m_direction--;
    }

    setRotation(m_direction);
}

QPointF EnemyModelType6::getFrontTurretStartPosition() {
    QPointF frontTurretStartPosition = getCenterPosition();
    frontTurretStartPosition.ry() -= def::enemyTurretFrontYCoordinateOffset;
    return frontTurretStartPosition;
}

QPointF EnemyModelType6::getMiddleTurretStartPosition() {
    QPointF middleTurretStartPosition = getCenterPosition();
    middleTurretStartPosition.ry() += def::enemyTurretMiddleYCoordinateOffset;
    return middleTurretStartPosition;
}

QPointF EnemyModelType6::getBackTurretStartPosition() {
    QPointF backTurretStartPosition = getCenterPosition();
    backTurretStartPosition.ry() += def::enemyTurretBackYCoordinateOffset;
    return backTurretStartPosition;
}
