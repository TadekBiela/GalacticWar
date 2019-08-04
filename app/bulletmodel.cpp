#include "bulletmodel.hpp"
#include "definitions.hpp"
#include <QtMath>

BulletModel::BulletModel(bullet_type type,
                         QPointF     position,
                         int         damage,
                         int         direction,
                         int         moveTimeDelay) :
                         m_type(type),
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
    int halfXaxisFactor = ((m_direction / 180) * 2 - 1) * -1; // Should be only 1 or -1
    int halfYaxisFactor = static_cast<bool>((m_direction / 90) % 3) * 2 - 1;
    qreal sinDirectionAngle = qFabs(qSin(m_direction * def::radianConversionFactor));
    qreal cosDirectionAngle = qFabs(qCos(m_direction * def::radianConversionFactor));
    qreal xOffset = sinDirectionAngle * def::moveVectorLength * halfXaxisFactor;
    qreal yOffset = cosDirectionAngle * def::moveVectorLength * halfYaxisFactor;

    QPointF position = pos();
    position.setX(position.x() + xOffset);
    position.setY(position.y() + yOffset);

    setPos(position);
}
