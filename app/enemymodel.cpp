#include "enemymodel.hpp"
#include "bulletmodel.hpp"
#include "functions.hpp"
#include "soundeffectmodel.hpp"
#include "animationeffectmodel.hpp"
#include <QGraphicsScene>
#include <typeinfo>

EnemyModel::EnemyModel(int level,
                       int health,
                       int damage,
                       int moveTimeDelay,
                       int fireTimeDelay,
                       int animationFrameWidth,
                       int animationFrameHeight)
    : GameObject(game_object_type::enemy),
      m_level(level),
      m_health(health),
      m_damage(damage),
      m_direction(0),
      m_animationFrameXIdx(0),
      m_animationFrameYIdx(0)
{
    m_image = g_imageStorage->getImage("enemy" + QString::number(level));

    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameXIdx,
                                animationFrameHeight * m_animationFrameYIdx,
                                animationFrameWidth,
                                animationFrameHeight));

    setTransformOriginPoint(pixmap().width()  / 2,
                            pixmap().height() / 2);

    connect(&m_moveTimer,      SIGNAL(timeout()), this, SLOT(move()));
    connect(&m_fireTimer,      SIGNAL(timeout()), this, SLOT(fire()));
    connect(&m_animationTimer, SIGNAL(timeout()), this, SLOT(animation()));
    m_moveTimer.setInterval(moveTimeDelay);
    m_fireTimer.setInterval(fireTimeDelay);
    m_animationTimer.setInterval(def::animationFrameDuration);
}

EnemyModel::~EnemyModel()
{

}

void EnemyModel::destroy()
{
    auto scene = QGraphicsItem::scene();
    scene->removeItem(this);
    QPointF positionOfDestroyedEnemy = getCenterPosition();
    emit this->destroyed(positionOfDestroyedEnemy, m_level);
    AnimationEffectModel* explosionAnim = new AnimationEffectModel("explosion",
                                                                   positionOfDestroyedEnemy,
                                                                   def::animationFrameWidth,
                                                                   def::animationFrameHeight);
    explosionAnim->play();
    SoundEffectModel* explosionSound = new SoundEffectModel("explosion");
    explosionSound->play();
    delete this;
}

void EnemyModel::start()
{
    m_moveTimer.start();
    m_fireTimer.start();
    m_animationTimer.start();
}

void EnemyModel::stop()
{
    m_moveTimer.stop();
    m_fireTimer.stop();
    m_animationTimer.stop();
}

void EnemyModel::animation()
{
    if(++m_animationFrameXIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameXIdx = 0;
    }

    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameXIdx,
                                pixmap().height() * m_animationFrameYIdx,
                                pixmap().width(),
                                pixmap().height()));
}

void EnemyModel::checkCollisions()
{
    auto scene          = QGraphicsItem::scene();
    auto collidingItems = scene->collidingItems(this);
    int  sumDamage      = 0;

    for(auto i = 0; i != collidingItems.size(); i++)
    {
        GameObject* collidingObject = dynamic_cast<GameObject*>(collidingItems[i]);
        if(game_object_type::player_bullet == collidingObject->getType())
        {
            BulletModel* bullet = static_cast<BulletModel*>(collidingItems[i]);
            sumDamage += bullet->getDamage();
            SoundEffectModel* hit = new SoundEffectModel("hit_enemy");
            hit->play();
            scene->removeItem(bullet);
            delete bullet;
        }
    }
    hit(sumDamage);
}

void EnemyModel::hit(int damage)
{
    m_health -= damage;
    if(m_health <= 0)
    {
        m_health = 0;
        destroy();
    }
}
