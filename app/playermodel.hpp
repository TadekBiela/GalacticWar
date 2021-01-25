
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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
