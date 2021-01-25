
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


#ifndef FIREFUNCTIONS_HPP
#define FIREFUNCTIONS_HPP

#include "definitions.hpp"
#include <QPointF>
#include <QGraphicsScene>

typedef void (*fire)(QGraphicsScene*, QPointF, int);

void defaultFireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);

void redLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void redLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void redLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void redLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void redLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);

void yellowLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void yellowLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void yellowLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void yellowLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void yellowLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);

void blueLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void blueLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void blueLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void blueLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);
void blueLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage);

void redExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
);

void yellowExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
);

void blueExtraBeamFireFunc(
    QGraphicsScene* scene,
    QPointF startPosition,
    int baseDamage
);

extern fire extraBeamAttack[def::maxWeaponTypes];

#endif // FIREFUNCTIONS_HPP
