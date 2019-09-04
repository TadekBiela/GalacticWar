#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "specialrewardtype.hpp"
#include "weapons.hpp"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>

class PlayerModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PlayerModel();
    ~PlayerModel();

signals:
    void playerChangeHealth(int healthPoints);

public slots:
    void move();
    void fire();
    void startFire();
    void stopFire();
    void changeDirection(QPointF newDirection);
    void changePlayerAtribute(special_reward_type specialReward);

protected:
    void changeWeapon(weapon_type weapon);

    bool   m_isMoving;
    int    m_direction;
    weapon m_weapon;
    int    m_moveTimeDelay;
    QTimer m_moveTimer;
    QTimer m_fireTimer;
};

#endif // PLAYERMODEL_HPP
