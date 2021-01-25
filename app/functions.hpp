
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


#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "definitions.hpp"
#include <QPointF>
#include <QPixmap>
#include <QImage>

//Changes false into -1 and true to 1
inline int changeBoolToMinusOneOrOne(bool value)
{
    return (static_cast<int>(value) * 2 - 1);
}

// direction should by in rane 0-359
QPointF calculateXYOffset(int direction, int distance);

QPointF moveForward(
    const QPointF startPosition,
    int direction,
    int distance = def::moveVectorLength
);

void rotatePointBasedOnCenterPoint(const QPointF centerPoint,
                                   const int     rotation,
                                   QPointF&      rotatedPoint);

bool isOutOfScene(QPointF pos, QPixmap pixmap);

QPixmap getAnimationFrame(QImage* image,
                          int     animFrameXIdx,
                          int     animFrameYIdx,
                          int     animationFrameWidth,
                          int     animationFrameHeight);

#endif // FUNCTIONS_HPP
