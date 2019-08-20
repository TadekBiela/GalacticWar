#include "enemymodel.hpp"
#include "definitions.hpp"

EnemyModel::EnemyModel(int     level,
                       QPointF position,
                       int     health,
                       int     damage,
                       int     moveTimeDelay,
                       int     fireTimeDelay)
                        : m_level(level),
                          m_health(health),
                          m_damage(damage),
                          m_animationFrameIdx(0)
{
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

void EnemyModel::destroy()
{
    emit this->destroyed(pos(), m_level);
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
