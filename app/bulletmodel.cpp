#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include "soundeffectmodel.hpp"

BulletModel::BulletModel(QString name,
                         QPointF position,
                         int     damage,
                         int     direction,
                         int     moveTimeDelay)
                          : m_name(name),
                            m_damage(damage)
{
    int finiteDirection = direction % 360;
    m_direction = finiteDirection < 0 ? 360 + finiteDirection : finiteDirection;

    //Setup QPixmap
    QPixmap map;
    map.convertFromImage(*g_imageStorage->getImage(m_name));
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

    SoundEffectModel* bulletSound = new SoundEffectModel(m_name);
}

BulletModel::~BulletModel()
{

}

QString BulletModel::getName() const
{
    return m_name;
}

int BulletModel::getDamage() const
{
    return m_damage;
}

void BulletModel::start()
{
    m_moveTimer.start();
}

void BulletModel::stop()
{
    m_moveTimer.stop();
}

void BulletModel::move()
{
    setPos(moveForward(pos(), m_direction));

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
    }
}
