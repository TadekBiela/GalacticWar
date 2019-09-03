#include "playermodel.hpp"
#include "definitions.hpp"
#include "firefunctions.hpp"
#include "functions.hpp"
#include <QLineF>

PlayerModel::PlayerModel() :
                         m_isMoving(false),
                         m_direction(0),
                         m_weapon(weapon_type::defaultWeapon),
                         m_damage(def::defaultPlayerDamage),
                         m_fireFuncPtr(&defaultFireFunc),
                         m_moveTimeDelay(def::defaultPlayerMoveTimeDelay),
                         m_fireTimeDelay(def::defaultPlayerFireTimeDelay)
{
    setPos(def::halfSceneWight, def::halfSceneHeight);

    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer, SIGNAL(timeout()), this, SLOT(fire()));
    m_moveTimer.setInterval(m_moveTimeDelay);
    m_fireTimer.setInterval(m_fireTimeDelay);

    m_moveTimer.start();
}

PlayerModel::~PlayerModel()
{

}

void PlayerModel::move()
{
    if(m_isMoving)
    {
        setPos(moveForward(pos(), m_direction));
    }
}

void PlayerModel::fire()
{
    m_fireFuncPtr(QGraphicsItem::pos(), m_damage);
}

void PlayerModel::startFire()
{
    m_fireTimer.setInterval(m_fireTimeDelay);
    m_fireTimer.start();
}

void PlayerModel::stopFire()
{
    m_fireTimer.stop();
}

void PlayerModel::changeDirection(QPointF newDirection)
{
    QLineF vector(QGraphicsItem::pos(), newDirection);
    int    length = static_cast<int>(vector.length());
    m_isMoving    = length >= def::moveVectorLength;
    m_direction   = static_cast<int>(360 + (vector.angle() - 90) * -1) % 360;
}

void PlayerModel::changePlayerAtribute(special_reward_type specialReward)
{

}

void PlayerModel::changeWeapon(weapon_type weapon)
{

}

