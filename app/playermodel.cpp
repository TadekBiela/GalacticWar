#include "playermodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "bulletmodel.hpp"
#include "enemymodel.hpp"
#include "rewardcoinmodel.hpp"
#include "rewardspecialmodel.hpp"
#include <QLineF>
#include <QGraphicsScene>
#include <typeinfo>

PlayerModel::PlayerModel()
                         : m_isMoving(false),
                           m_direction(0),
                           m_health(def::maxPlayerHealth),
                           m_weapon(defaultWeapon),
                           m_weaponTier(0),
                           m_moveTimeDelay(def::defaultPlayerMoveTimeDelay)
{
    //temporary simple graphic
    QPixmap map(QSize(60, 60));
    map.fill(Qt::green);
    setPixmap(map);

    setPos(def::halfSceneWight, def::halfSceneHeight);

    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer, SIGNAL(timeout()), this, SLOT(fire()));
    m_moveTimer.setInterval(m_moveTimeDelay);
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
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

    //Check collisions
    auto scene           = QGraphicsItem::scene();
    auto collidingItems  = scene->collidingItems(this);
    int  numOfCollisions = collidingItems.size();
    for(auto i = 0; i != collidingItems.size(); i++)
    {
        if(typeid(*collidingItems[i]) == typeid(BulletModel))
        {
            BulletModel* bullet = static_cast<BulletModel*>(collidingItems[i]);
            if(bullet->getType() == bullet_type::enemyBullet)
            {
                m_health -= bullet->getDamage();
                scene->removeItem(collidingItems[i]);
                delete collidingItems[i];
            }
            else
            {
                numOfCollisions--;
            }
        }
        else if(typeid(*collidingItems[i]) == typeid(RewardCoinModel) ||
                typeid(*collidingItems[i]) == typeid(RewardSpecialModel))
        {
            RewardModel* coin = static_cast<RewardModel*>(collidingItems[i]);
            scene->removeItem(collidingItems[i]);
            coin->collect();
            numOfCollisions--;
        }
        else //It should be Enemy
        {
            EnemyModel* enemy = static_cast<EnemyModel*>(collidingItems[i]);
            m_health -= enemy->getLevel() * 100;
            enemy->destroy();
        }
    }

    if(m_health <= 0)
    {
        m_health = 0;
        emit changeHealth(0);
        scene->removeItem(this);
        emit defeated();
    }
    else if(numOfCollisions > 0)
    {
        emit changeHealth(m_health);
    }
}

void PlayerModel::fire()
{
    m_weapon.fireFuncPtr(QGraphicsItem::pos(), m_weapon.damage);
}

void PlayerModel::startFire()
{
    m_fireTimer.start();
}

void PlayerModel::stopFire()
{
    m_fireTimer.stop();
}

void PlayerModel::changeDirection(QPointF newDirection)
{
    QLineF vector(QGraphicsItem::pos(), newDirection);
    int length  = static_cast<int>(vector.length());
    m_isMoving  = length >= def::moveVectorLength;
    m_direction = static_cast<int>(360 + (vector.angle() - 90) * -1) % 360;
}

void PlayerModel::changeAtribute(special_type specialReward)
{
    switch (specialReward)
    {
        case special_type::health:
            m_health = m_health + 100 > def::maxPlayerHealth ? def::maxPlayerHealth : m_health + 100;
            emit changeHealth(m_health / 10);
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
        m_weapon     = weapons[weapon * def::maxWeaponLevel];
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
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
}

