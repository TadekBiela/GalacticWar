#include "bulletmodel.hpp"

BulletModel::BulletModel(bullet_type type,
                         QPointF     position,
                         int         damage,
                         int         direction,
                         int         moveTimeDelay)
{

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

}
