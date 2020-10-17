#include "enemymodeltype6.hpp"
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
    if(startPosition.x() <= def::halfSceneWight) {
        startXCoordinate = 0 - def::enemy6StartXCoordinateOffset;
        m_direction = def::right + directionOffset;
        m_rotationDirection = enemy_rotation_direction::right;
        m_frontTurret = new EnemyTurret(
            this,
            enemy_turret_type::double_cannons,
            getFrontTurretStartPosition(),
            20,
            1000,
            45,
            enemy_turret_rotate_direction::right,
            100
        );
    }
    else {
        startXCoordinate = def::sceneWight + def::enemy6StartXCoordinateOffset;
        m_direction = def::left - directionOffset;
        m_rotationDirection = enemy_rotation_direction::left;
        m_frontTurret = new EnemyTurret(
            this,
            enemy_turret_type::double_cannons,
            getFrontTurretStartPosition(),
            20,
            1000,
            45,
            enemy_turret_rotate_direction::left,
            100
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
}

void EnemyModelType6::stop() {
    EnemyModel::stop();
    m_frontTurret->stop();
}

void EnemyModelType6::fire() {

}

void EnemyModelType6::move() {
    const int movePositionOffset = 2;
    setPos(moveForward(pos(), m_direction, movePositionOffset));

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
    QPointF frontTurretStartPosition;
    const int frontTurretenemy6startXCoordinateOffsetInPx = 90;
    frontTurretStartPosition.setX(
        pos().x() +
        (pixmap().width() / 2)
    );
    frontTurretStartPosition.setY(
        pos().y() +
        frontTurretenemy6startXCoordinateOffsetInPx
    );
    return frontTurretStartPosition;
}
