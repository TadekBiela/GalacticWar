#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"

BulletModel::BulletModel(bullet_type type,
                         QPointF     position,
                         int         damage,
                         int         direction,
                         int         moveTimeDelay)
                          : m_type(type),
                            m_damage(damage)
{
    int finiteDirection = direction % 360;
    m_direction = finiteDirection < 0 ? 360 + finiteDirection : finiteDirection;

    //Setup QPixmap
    setPos(position);
    setRotation(m_direction);

    //Setup move timer
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    m_moveTimer.setInterval(moveTimeDelay);
    m_moveTimer.start();
}

BulletModel::~BulletModel()
{

}

bullet_type BulletModel::getType() const
{
    return m_type;
}

int BulletModel::getDamage() const
{
    return m_damage;
}

void BulletModel::move()
{
    setPos(moveForward(pos(), m_direction));
}
