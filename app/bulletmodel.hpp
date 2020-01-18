#ifndef BULLETMODEL_HPP
#define BULLETMODEL_HPP

#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>

class BulletModel : public GameObject
{
    Q_OBJECT
public:
    BulletModel(QString name,
                QPointF position,
                int     damage,
                int     direction,
                int     moveTimeDelay,
                float   pixmapScaleFactor = 1);
    virtual ~BulletModel();
    QString getName() const;
    int     getDamage() const;

public slots:
    void start();
    void stop();
    void move();

protected:
    QString m_name;
    int     m_damage;
    int     m_direction;
    QTimer  m_moveTimer;
};

#endif //BULLETMODEL_HPP
