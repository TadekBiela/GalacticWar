
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


#ifndef ENEMYMODELTYPE4_HPP
#define ENEMYMODELTYPE4_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_jump_side {
    left,
    right
};

class EnemyModelType4 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType4(
        QPointF position
    );
    virtual ~EnemyModelType4();

public slots:
    void fire();
    void move();

private:
    void jumpMove();

protected:
    int m_jumpMoveTimeDelay;
    bool m_isJumpMove;
    enemy_jump_side m_jumpSide;
};

#endif // ENEMYMODELTYPE4_HPP
