
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


#ifndef ENEMYMODELTYPE5_HPP
#define ENEMYMODELTYPE5_HPP

#include "enemymodel.hpp"
#include <QPointF>

enum enemy_weapon {
    mode_first_element = 0,
    mode_small         = 0,
    mode_medium        = 1,
    mode_big           = 2,
    mode_last_element  = 2
};

enum class enemy_move_side {
    left,
    right
};

typedef void (*fireEnemy)(
    QPointF position,
    QGraphicsScene* scene
);

class EnemyModelType5 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType5(
        QPointF position
    );
    virtual ~EnemyModelType5();

public slots:
    void fire();
    void move();

private:
    void changeMoveSide();

protected:
    const static fireEnemy s_weapons[enemy_weapon::mode_last_element + 1];

    enemy_weapon m_weaponMode;
    int m_changeMoveSideTimeDelay;
    enemy_move_side m_moveSide;
};

#endif // ENEMYMODELTYPE5_HPP
