
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


#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include "definitions.hpp"
#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>
#include <QImage>
#include <QPixmap>

enum class enemy_rotation_direction {
    left,
    right
};

class EnemyModel : public GameObject
{
    Q_OBJECT
public:
    EnemyModel(int level,
               int health,
               int damage,
               int moveTimeDelay,
               int fireTimeDelay,
               int animationFrameWidth  = def::animationFrameWidth,
               int animationFrameHeight = def::animationFrameHeight);
    virtual ~EnemyModel();
    void destroy();
    int getLevel() const { return m_level; }

signals:
    void destroyed(QPointF position, int level);

public slots:
    virtual void start();
    virtual void stop();

protected slots:
    virtual void fire() = 0;
    virtual void move() = 0;
    virtual void animation();

protected:
    void checkCollisions();
    void hit(int damage);

    QImage* m_image;
    int m_level;
    int m_health;
    int m_damage;
    int m_direction;
    int m_animationFrameXIdx;
    int m_animationFrameYIdx;
    QTimer m_fireTimer;
    QTimer m_moveTimer;
    QTimer m_animationTimer;
};

#endif // ENEMYMODEL_HPP
