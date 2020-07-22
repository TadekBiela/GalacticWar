#ifndef BULLETMODEL_HPP
#define BULLETMODEL_HPP

#include "gameobject.hpp"
#include <QPointF>
#include <QString>
#include <QTimer>

class BulletModel : public GameObject
{
    Q_OBJECT
public:
    BulletModel(QString          graphicsName,
                game_object_type type,
                QPointF          position,
                int              damage,
                int              direction,
                int              moveTimeDelay,
                float            pixmapScaleFactor = 1);
    virtual ~BulletModel();
    int getDamage() const;

public slots:
    void start();
    void stop();

protected slots:
    void move();

protected:
    int    m_damage;
    int    m_direction;
    QTimer m_moveTimer;
};

#endif //BULLETMODEL_HPP
