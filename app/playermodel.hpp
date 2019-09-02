#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "firefunctions.hpp"
#include "specialrewardtype.hpp"
#include "weapontype.hpp"
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
    void playerHit(int damage);

public slots:
    void move();
    void fire();
    void stopFire();
    void changeDirection();
    void changePlayerAtribute(special_reward_type specialReward);

protected:
    void changeWeapon(weapon_type weapon);

    QPointF     m_moveDirection;
    int         m_moveTypeDelay;
    weapon_type m_weapon;
    ::fire      m_fireFuncPtr;
    QTimer      m_moveTimer;
    QTimer      m_fireTimer;
};

#endif // PLAYERMODEL_HPP
