
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


#ifndef ENEMYMODELTYPE6_HPP
#define ENEMYMODELTYPE6_HPP

#include "enemymodel.hpp"
#include "enemyturret.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType6 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType6(
        QPointF position,
        IRandomGenerator* generator
    );
    virtual ~EnemyModelType6();

public slots:
    void start() override;
    void stop() override;

protected slots:
    void fire() override;
    void move() override;

private:
    QPointF getFrontTurretStartPosition();
    QPointF getMiddleTurretStartPosition();
    QPointF getBackTurretStartPosition();
    void rotate();

protected:
    int m_rotationTimeDelay;
    int m_rotationCounter;
    enemy_rotation_direction m_rotationDirection;
    EnemyTurret* m_frontTurret;
    EnemyTurret* m_middleTurret;
    EnemyTurret* m_backTurret;
};

#endif // ENEMYMODELTYPE6_HPP
