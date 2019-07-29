#ifndef BULLETMODEL_H
#define BULLETMODEL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bullettype.hpp"

class BulletModel : public QObject, public ::QGraphicsPixmapItem
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
    int         m_moveTimeDelay;
    QTimer      m_moveTimer;
};

#endif //BULLETMODEL_H
