#include "playermodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include "animationeffectmodel.hpp"
#include "bulletmodel.hpp"
#include "enemymodel.hpp"
#include "rewardcoinmodel.hpp"
#include "rewardspecialmodel.hpp"
#include "soundeffectmodel.hpp"
#include <QLineF>
#include <QGraphicsScene>
#include <typeinfo>

PlayerModel::PlayerModel()
                         : m_movePosition(QPointF(def::halfSceneWight, def::halfSceneHeight)),
                           m_direction(0),
                           m_health(def::maxPlayerHealth),
                           m_weapon(defaultWeapon),
                           m_weaponTier(0),
                           m_moveTimeDelay(def::defaultPlayerMoveTimeDelay),
                           m_animationFrameIdx(0)
{
    m_image = g_imageStorage->getImage("player");
    setPixmap(getAnimationFrame(m_image, m_animationFrameIdx));

    setPos(def::halfSceneWight  - def::animationFrameWight  / 2,
           def::halfSceneHeight - def::animationFrameHeight / 2);

    connect(&m_moveTimer,      SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer,      SIGNAL(timeout()), this, SLOT(fire()));
    connect(&m_animationTimer, SIGNAL(timeout()), this, SLOT(animation()));

    m_moveTimer.setInterval(m_moveTimeDelay);
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
    m_animationTimer.setInterval(def::animationFrameDuration);
}

PlayerModel::~PlayerModel()
{

}

void PlayerModel::start()
{
    m_moveTimer.start();
    m_animationTimer.start();
}

void PlayerModel::stop()
{
    m_moveTimer.stop();
    m_fireTimer.stop();
    m_animationTimer.stop();
}

bool PlayerModel::isOnMovePosition()
{
    QPointF currentPosition = QGraphicsItem::pos();
    currentPosition.setX(currentPosition.x() + def::animationFrameWight  / 2);
    currentPosition.setY(currentPosition.y() + def::animationFrameHeight / 2);

    QLineF vector(currentPosition, m_movePosition);
    m_direction = static_cast<int>(360 + (vector.angle() - 90) * -1) % 360;

    int  length      = static_cast<int>(vector.length());
    bool isOnMovePos = length <= def::moveVectorLength;
    return isOnMovePos;
}

void PlayerModel::checkCollisions()
{
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
            RewardModel* reward = static_cast<RewardModel*>(collidingItems[i]);
            reward->collect();
            numOfCollisions--;
        }
        else if(typeid(*collidingItems[i]) == typeid(AnimationEffectModel))
        {
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
        emit defeated();
    }
    else if(numOfCollisions > 0)
    {
        emit changeHealth(m_health / 10);
        SoundEffectModel* hitSound = new SoundEffectModel("hit_player");
    }
    scene->update();
}

void PlayerModel::move()
{
    if(isOnMovePosition() == false)
    {
        QPointF newPosition(moveForward(pos(), m_direction));
        int x = newPosition.x();
        int y = newPosition.y();
        int minX = 0;
        int maxX = def::sceneWight - pixmap().size().width();
        int minY = 0;
        int maxY = def::sceneHeight - pixmap().size().height();

        if(x >= minX && x <= maxX && y >= minY && y <= maxY)
        {
            setPos(newPosition);
        }
    }

    checkCollisions();
}

void PlayerModel::fire()
{
    QPointF position = QGraphicsItem::pos();
    position.setX(position.x() + def::animationFrameWight / 2);
    m_weapon.fireFuncPtr(QGraphicsItem::scene(), position, m_weapon.damage);
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
}

void PlayerModel::startFire()
{
    m_fireTimer.setInterval(100);
    m_fireTimer.start();
}

void PlayerModel::stopFire()
{
    m_fireTimer.stop();
}

void PlayerModel::changeMovePosition(QPointF newMovePosition)
{
    m_movePosition = newMovePosition;
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

void PlayerModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }

    setPixmap(getAnimationFrame(m_image, m_animationFrameIdx));
}
