#include "playermodel.hpp"
#include "definitions.hpp"
#include "firefunctions.hpp"

PlayerModel::PlayerModel() :
                         m_moveDirection(def::halfSceneWight, def::halfSceneHeight),
                         m_weapon(weapon_type::defaultWeapon),
                         m_fireFuncPtr(&defaultFireFunc)
{
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer, SIGNAL(timeout()), this, SLOT(fire()));
}

PlayerModel::~PlayerModel()
{

}

void PlayerModel::move()
{

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

