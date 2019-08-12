#ifndef BULLETMODEL_H
#define BULLETMODEL_H

#include "gameobject.hpp"
#include "bullettype.hpp"
#include <QPointF>
#include <QTimer>

class BulletModel : public GameObject
{
    Q_OBJECT
public:
    BulletModel(bullet_type type,
                QPointF     position,
                int         damage,
                int         direction,
                int         moveTimeDelay);
    ~BulletModel();
    bullet_type getType() const;
    int         getDamage() const;
public slots:
    void move();
protected:
    bullet_type m_type;
    int         m_damage;
    int         m_direction;
    QTimer      m_moveTimer;
};

#endif //BULLETMODEL_H
