#include "playermodel.hpp"
#include "definitions.hpp"
#include "firefunctions.hpp"
#include "functions.hpp"
#include <QLineF>

PlayerModel::PlayerModel() :
                         m_moveDirection(def::halfSceneWight, def::halfSceneHeight),
                         m_weapon(weapon_type::defaultWeapon),
                         m_fireFuncPtr(&defaultFireFunc)
{
    setPos(m_moveDirection);
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer, SIGNAL(timeout()), this, SLOT(fire()));
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

}

void PlayerModel::stopFire()
{

}

void PlayerModel::changeDirection()
{

}

void PlayerModel::changePlayerAtribute(special_reward_type specialReward)
{

}

void PlayerModel::changeWeapon(weapon_type weapon)
{

}

