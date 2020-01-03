#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "rewardtypes.hpp"
#include "weapons.hpp"
#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>
#include <QImage>

class PlayerModel : public GameObject
{
    Q_OBJECT
public:
    PlayerModel();
    virtual ~PlayerModel();
    void setHealth(int health) { m_health = health; }
    int  getHealth() const { return m_health; }
    bool isOnMovePosition();
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
    void changeMovePosition(QPointF newMovePosition);
    void changeAtribute(special_type specialReward);
    void animation();

protected:
    void    changeWeapon(weapon_type weapon);

    QImage* m_image;
    QPointF m_movePosition;
    int     m_direction;
    int     m_health;
    weapon  m_weapon;
    int     m_weaponTier;
    int     m_moveTimeDelay;
    QTimer  m_moveTimer;
    QTimer  m_fireTimer;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
};

#endif // PLAYERMODEL_HPP
