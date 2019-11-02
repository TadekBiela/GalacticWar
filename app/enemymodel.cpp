#include "enemymodel.hpp"
#include "definitions.hpp"
#include "bulletmodel.hpp"
#include <QGraphicsScene>
#include <typeinfo>

EnemyModel::EnemyModel(int     level,
                       QPointF position,
                       int     health,
                       int     damage,
                       int     moveTimeDelay,
                       int     fireTimeDelay)
                        : m_level(level),
                          m_health(health),
                          m_damage(damage),
                          m_direction(0),
                          m_animationFrameIdx(0)
{
    //temporary simple graphic
    QPixmap map(QSize(def::animationFrameWight, def::animationFrameHeight));
    map.fill(Qt::red);
    setPixmap(map);

    position.setX(position.x() - def::animationFrameWight  / 2);
    position.setY(position.y() - def::animationFrameHeight / 2);
    setPos(position);

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

void EnemyModel::checkCollisions()
{
    auto scene          = QGraphicsItem::scene();
    auto collidingItems = scene->collidingItems(this);

    for(auto i = 0; i != collidingItems.size(); i++)
    {
        if(typeid(*collidingItems[i]) == typeid(BulletModel))
        {
            BulletModel* bullet = static_cast<BulletModel*>(collidingItems[i]);
            if(bullet->getType() != bullet_type::enemyBullet)
            {
                hit(bullet->getDamage());
                scene->removeItem(collidingItems[i]);
                delete collidingItems[i];
            }
        }
    }
}

void EnemyModel::destroy()
{
    auto scene = QGraphicsItem::scene();
    scene->removeItem(this);
    QPointF position = pos();
    position.setX(position.x() + def::animationFrameWight  / 2);
    position.setY(position.y() + def::animationFrameHeight / 2);
    emit this->destroyed(position, m_level);
    delete this;
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
