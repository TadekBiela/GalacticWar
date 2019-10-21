#ifndef BULLETMODEL_HPP
#define BULLETMODEL_HPP

#include "bullettype.hpp"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>

class BulletModel : public QObject, public QGraphicsPixmapItem
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
    void move();

protected:
    bullet_type m_type;
    int         m_damage;
    int         m_direction;
    QTimer      m_moveTimer;
};

#endif //BULLETMODEL_HPP
