#ifndef BULLETMODEL_HPP
#define BULLETMODEL_HPP

#include "bullettype.hpp"
#include "gameobject.hpp"
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
    virtual ~BulletModel();
    bullet_type getType() const;
    int         getDamage() const;

public slots:
    void start();
    void stop();
    void move();

protected:
    void playSound();

    bullet_type m_type;
    int         m_damage;
    int         m_direction;
    QTimer      m_moveTimer;
};

#endif //BULLETMODEL_HPP
