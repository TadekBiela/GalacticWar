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
    : GameObject(game_object_type::player),
      m_movePosition(QPointF(def::halfSceneWidth, def::halfSceneHeight)),
      m_direction(0),
      m_weapon(defaultWeapon),
      m_weaponTier(0),
      m_moveTimeDelay(def::defaultPlayerMoveTimeDelay),
      m_moveTimer(),
      m_fireTimer(),
      m_animationFrameIdx(0),
      m_animationTimer()
{
    m_image = g_imageStorage->getImage("player");
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                def::animationFrameWidth,
                                def::animationFrameHeight));

    setCenterPosition(def::halfSceneWidth, def::halfSceneHeight);

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

void PlayerModel::hit(int damage)
{
    emit subtractHealthPoints(damage);
    SoundEffectModel* hitSound = new SoundEffectModel("hit_player");
    hitSound->play();
}

bool PlayerModel::isOnMovePosition()
{
    QPointF currentPosition = getCenterPosition();

    QLineF vector(currentPosition, m_movePosition);
    const int maxDegreeValue = 360;
    m_direction = static_cast<int>(maxDegreeValue + ((vector.angle() - 90) * -1)) % maxDegreeValue;

    int length = static_cast<int>(vector.length());
    bool isOnMovePos = (length <= def::moveVectorLength);
    return isOnMovePos;
}

void PlayerModel::checkCollisions()
{
    auto scene          = QGraphicsItem::scene();
    auto collidingItems = scene->collidingItems(this);
    for(auto i = 0; i != collidingItems.size(); i++)
    {
        GameObject* collidingObject = dynamic_cast<GameObject*>(collidingItems[i]);
        switch(collidingObject->getType())
        {
            case game_object_type::enemy_bullet:
            {
                BulletModel* bullet = dynamic_cast<BulletModel*>(collidingObject);
                this->hit(bullet->getDamage());
                scene->removeItem(bullet);
                delete bullet;
                break;
            }
            case game_object_type::reward:
            {
                RewardModel* reward = dynamic_cast<RewardModel*>(collidingObject);
                reward->collect();
                break;
            }
            case game_object_type::enemy:
            {
                EnemyModel* enemy = dynamic_cast<EnemyModel*>(collidingObject);
                int damage = enemy->getLevel() * def::collisionDamageFactor;
                this->hit(damage);
                enemy->destroy();
                break;
            }
            default:
            {
                break;
            }
        }
    }
    scene->update();
}

void PlayerModel::changeWeapon(weapon_type weapon){
    if(weapon != m_weapon.type){
        m_weapon = weapons[weapon * def::maxWeaponLevel];
        m_weaponTier = 0;
    }
    else{
        if(m_weaponTier < def::maxWeaponLevelIdx){
            m_weaponTier++;
        }
        else {
            extraBeamAttack[m_weapon.type](
                QGraphicsItem::scene(),
                getCenterPosition(),
                m_weapon.damage
            );
        }
        m_weapon = weapons[(weapon * def::maxWeaponLevel) + m_weaponTier];
    }
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
}

void PlayerModel::move()
{
    if(not isOnMovePosition())
    {
        QPointF newPosition(moveForward(pos(), m_direction));
        int x = newPosition.x();
        int y = newPosition.y();
        int minX = 0;
        int maxX = def::sceneWidth - pixmap().size().width();
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
    QPointF position = getCenterPosition();
    position.setY(position.y() - def::animationFrameHeight / 2);
    m_weapon.fireFuncPtr(QGraphicsItem::scene(), position, m_weapon.damage);
    m_fireTimer.setInterval(m_weapon.fireTimeDelay);
}

void PlayerModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }
    int animYIdx = 0;
    switch(m_direction / 30)
    {
        case 2:
        case 3:
        case 4:
            animYIdx = 2;
            break;
        case 8:
        case 9:
        case 10:
            animYIdx = 1;
    }
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                def::animationFrameHeight * animYIdx,
                                def::animationFrameWidth,
                                def::animationFrameHeight));
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

void PlayerModel::startFire()
{
    m_fireTimer.setInterval(def::defaultPlayerFireTimeDelay);
    m_fireTimer.start();
}

void PlayerModel::stopMoveOnAxeX() {
    m_movePosition.setX(getCenterPosition().x());
    emit getCurrentPosition(m_movePosition);
}

void PlayerModel::stopMoveOnAxeY() {
    m_movePosition.setY(getCenterPosition().y());
    emit getCurrentPosition(m_movePosition);
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
    switch(specialReward)
    {
        case special_type::health:
            emit addHealthPoints(def::healthRewardValue);
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
