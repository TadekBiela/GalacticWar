#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include "soundeffectmodel.hpp"

BulletModel::BulletModel(QString          graphicsName,
                         game_object_type type,
                         QPointF          position,
                         int              damage,
                         int              direction,
                         int              moveTimeDelay,
                         float            pixmapScaleFactor)
    : GameObject(type),
      m_damage(damage),
      m_direction(0),
      m_moveTimer()
{
    int finiteDirection = direction % 360;
    m_direction = finiteDirection < 0 ? 360 + finiteDirection : finiteDirection;

    //Setup QPixmap
    QPixmap map;
    map.convertFromImage(*g_imageStorage->getImage(graphicsName));
    setPixmap(map.scaled(map.width()  * pixmapScaleFactor,
                         map.height() * pixmapScaleFactor));

    setTransformOriginPoint(pixmap().size().width()  / 2,
                            pixmap().size().height() / 2);

    setCenterPosition(position);
    setRotation(m_direction);

    //Setup move timer
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    m_moveTimer.setInterval(moveTimeDelay);
    m_moveTimer.start();

    QString soundName = graphicsName;
    SoundEffectModel* bulletSound = new SoundEffectModel(soundName);
    bulletSound->play();
}

BulletModel::~BulletModel()
{

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
