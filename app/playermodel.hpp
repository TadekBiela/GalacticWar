#ifndef PLAYERMODEL_HPP
#define PLAYERMODEL_HPP

#include "gameobject.hpp"
#include "rewardtypes.hpp"
#include "weapons.hpp"
#include <QImage>
#include <QPointF>
#include <QTimer>

class PlayerModel : public GameObject
{
    Q_OBJECT
public:
    PlayerModel();
    virtual ~PlayerModel();

signals:
    void addHealthPoints(int healthPoints);
    void subtractHealthPoints(int healthPoints);
    void getCurrentPosition(QPointF currentPosition);

public slots:
    void start();
    void stop();
    void startFire();
    void stopFire();
    void stopMoveOnAxeX();
    void stopMoveOnAxeY();
    void changeMovePosition(QPointF newMovePosition);
    void changeAtribute(special_type specialReward);

protected slots:
    void move();
    void fire();
    void animation();

protected:
    void hit(int damage);
    bool isOnMovePosition();
    void checkCollisions();
    void changeWeapon(weapon_type weapon);

    QImage* m_image;
    QPointF m_movePosition;
    int     m_direction;
    weapon  m_weapon;
    int     m_weaponTier;
    int     m_moveTimeDelay;
    QTimer  m_moveTimer;
    QTimer  m_fireTimer;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
};

#endif // PLAYERMODEL_HPP
