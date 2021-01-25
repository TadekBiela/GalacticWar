
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


#ifndef ENEMYMODELTYPE1_HPP
#define ENEMYMODELTYPE1_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType1 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType1(
        QPointF position,
        IRandomGenerator* generator
    );
    virtual ~EnemyModelType1();

public slots:
    void fire();
    void move();
};

#endif // ENEMYMODELTYPE1_HPP
