#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "rewardtypes.hpp"
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
    virtual ~PlayerModel();
    void setHealth(int health) { m_health = health; }
    int getHealth() const { return m_health; }
    void checkCollisions();

signals:
    void changeHealth(int healthPoints);
    void defeated();

public slots:
    void start();
    void stop();
    void move();
    void fire();
    void startFire();
    void stopFire();
    void changeDirection(QPointF newDirection);
    void changeAtribute(special_type specialReward);

protected:
    void changeWeapon(weapon_type weapon);

    bool   m_isMoving;
    int    m_direction;
    int    m_health;
    weapon m_weapon;
    int    m_weaponTier;
    int    m_moveTimeDelay;
    QTimer m_moveTimer;
    QTimer m_fireTimer;
};

#endif // PLAYERMODEL_HPP
