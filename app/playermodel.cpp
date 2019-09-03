#include "playermodel.hpp"
#include "definitions.hpp"
#include "firefunctions.hpp"
#include "functions.hpp"
#include <QLineF>

PlayerModel::PlayerModel() :
                         m_moveDirection(def::halfSceneWight, def::halfSceneHeight),
                         m_weapon(weapon_type::defaultWeapon),
                         m_damage(def::defaultPlayerDamage),
                         m_fireFuncPtr(&defaultFireFunc),
                         m_moveTimeDelay(def::defaultPlayerMoveTimeDelay),
                         m_fireTimeDelay(def::defaultPlayerFireTimeDelay)
{
    setPos(m_moveDirection);

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
    QLineF vector(QGraphicsItem::pos(), m_moveDirection);
    int    length = static_cast<int>(vector.length());

    if(length >= def::moveVectorLength)
    {
        int direction = static_cast<int>(360 + (vector.angle() - 90) * -1) % 360;
        setPos(moveForward(pos(), direction));
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
    m_moveDirection = newDirection;
}

void PlayerModel::changePlayerAtribute(special_reward_type specialReward)
{

}

void PlayerModel::changeWeapon(weapon_type weapon)
{

}

