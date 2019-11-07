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
    //temporary simple graphic
    QPixmap map(QSize(4, 10));
    map.fill(Qt::black);
    setPixmap(map);

    setTransformOriginPoint(pixmap().size().width()  / 2,
                            pixmap().size().height() / 2);

    position.setX(position.x() - pixmap().size().width()  / 2);
    position.setY(position.y() - pixmap().size().height() / 2);
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

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
    }
}
