#include "enemymodeltype6.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>
#include <cmath>

namespace def
{

const int enemy6Level = 6;
const int enemy6MaxHealthPoints = 2000;
const int enemy6BaseDamage = 0;
const int enemy6MoveTimeDelay = 100;
const int enemy6FireTimeDelay = 1000;
const int enemy6animationFrameWidth = 64;
const int enemy6animationFrameHeight = 256;
const int enemy6MinStartYCoordinate = -48;
const int enemy6MaxStartYCoordinate = 68;
const int enemy6MinRotationManeuverDegrees = 65;
const int enemy6MaxRotationManeuverDegrees = 80;
const int enemy6MinRotationManeuverTime = 28000;
const int enemy6MaxRotationManeuverTime = 32000;

}

EnemyModelType6::EnemyModelType6(QPointF startPosition,
                                 IRandomGenerator* generator)
    : EnemyModel(def::enemy6Level,
                 def::enemy6MaxHealthPoints,
                 def::enemy6BaseDamage,
                 def::enemy6MoveTimeDelay,
                 def::enemy6FireTimeDelay,
                 def::enemy6animationFrameWidth,
                 def::enemy6animationFrameHeight),
      m_remainigManeuverTime(0),
      m_maneuverTimer(),
      m_isCarryOutRotationManeuver(false),
      m_rotateTimer()
{
    int startXCoordinate = 0;
    int startXCoordinateOffset = 112;
    m_rotationCounter = generator->bounded(def::enemy6MinRotationManeuverDegrees,
                                           def::enemy6MaxRotationManeuverDegrees);
    const int directionOffset = def::right - m_rotationCounter;
    if(startPosition.x() <= def::halfSceneWight)
    {
        startXCoordinate = 0 - startXCoordinateOffset;
        m_direction = def::right + directionOffset;
        m_rotationDirection = enemy_rotation_direction::right;
    }
    else
    {
        startXCoordinate = (def::sceneWight) + startXCoordinateOffset;
        m_direction = def::left - directionOffset;
        m_rotationDirection = enemy_rotation_direction::left;
    }

    setRotation(m_direction);
    int startYCoordinate = generator->bounded(def::enemy6MinStartYCoordinate,
                                              def::enemy6MaxStartYCoordinate);
    startPosition.setX(startXCoordinate);
    startPosition.setY(startYCoordinate);
    setStartPosition(startPosition);

    connect(&m_maneuverTimer, SIGNAL(timeout()), this, SLOT(startManeuver()));
    m_remainigManeuverTime = generator->bounded(def::enemy6MinRotationManeuverTime,
                                                def::enemy6MaxRotationManeuverTime);
    m_maneuverTimer.setInterval(m_remainigManeuverTime);

    connect(&m_rotateTimer, SIGNAL(timeout()), this, SLOT(rotate()));
    m_rotateTimer.setInterval(m_moveTimer.interval());
}

EnemyModelType6::~EnemyModelType6()
{

}

void EnemyModelType6::start()
{
    EnemyModel::start();
    m_maneuverTimer.start(m_remainigManeuverTime);
    if(m_isCarryOutRotationManeuver)
    {
        m_rotateTimer.start();
    }
}

void EnemyModelType6::stop()
{
    EnemyModel::stop();
    m_remainigManeuverTime = m_maneuverTimer.remainingTime();
    m_maneuverTimer.stop();

    if(m_isCarryOutRotationManeuver)
    {
        m_rotateTimer.stop();
    }
}

void EnemyModelType6::fire()
{

}

void EnemyModelType6::move()
{
    const int movePositionOffset = 2;
    setPos(moveForward(pos(), m_direction, movePositionOffset));

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }

    checkCollisions();
}

void EnemyModelType6::startManeuver()
{
    m_remainigManeuverTime = -1;
    m_isCarryOutRotationManeuver = true;
    m_rotateTimer.start();
}

void EnemyModelType6::stopManeuver()
{
    m_isCarryOutRotationManeuver = false;
    m_rotateTimer.stop();
}

void EnemyModelType6::rotate()
{
    m_rotationCounter--;

    if(m_rotationCounter <= 0)
    {
        stopManeuver();
        return;
    }

    if(enemy_rotation_direction::right == m_rotationDirection)
    {
        m_direction++;
    }
    else
    {
        m_direction--;
    }
    setRotation(m_direction);
}
