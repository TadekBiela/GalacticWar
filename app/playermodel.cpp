#include "playermodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QLineF>

PlayerModel::PlayerModel() :
                         m_isMoving(false),
                         m_direction(0),
                         m_weapon(defaultWeapon),
                         m_weaponTier(0),
                         m_moveTimeDelay(def::defaultPlayerMoveTimeDelay)
{
    setPos(def::halfSceneWight, def::halfSceneHeight);

    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer, SIGNAL(timeout()), this, SLOT(fire()));
    m_moveTimer.setInterval(m_moveTimeDelay);
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);

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
    m_weapon.fireFuncPtr(QGraphicsItem::pos(), m_weapon.damage);
}

void PlayerModel::startFire()
{
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
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

void PlayerModel::changePlayerAtribute(special_type specialReward)
{
    switch (specialReward)
    {
        case special_type::health:
            emit playerChangeHealth(100);
            break;
        case special_type::weaponRed:
            changeWeapon(weapon_type::redWeapon);
            break;
        case special_type::weaponYellow:
            changeWeapon(weapon_type::yellowWeapon);
            break;
        case special_type::weaponBlue:
            changeWeapon(weapon_type::blueWeapon);
            break;
    }
}

void PlayerModel::changeWeapon(weapon_type weapon)
{
    if(weapon != m_weapon.type)
    {
        m_weapon = weapons[weapon * def::maxWeaponLevel];
        m_weaponTier = 0;
    }
    else
    {
        if(m_weaponTier < 4)
        {
            m_weaponTier++;
        }
        m_weapon = weapons[(weapon * def::maxWeaponLevel) + m_weaponTier];
    }
    startFire();
}

