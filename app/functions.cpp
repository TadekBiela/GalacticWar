
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


#include "functions.hpp"
#include <QtMath>
#include <algorithm>

QPointF calculateXYOffset(int direction, int distance)
{
    int halfXaxisFactor = changeBoolToMinusOneOrOne(static_cast<bool>(direction / 180)) * -1;
    int halfYaxisFactor = changeBoolToMinusOneOrOne(static_cast<bool>(((direction / 90) % 3)));
    qreal sinDirectionAngle = qFabs(qSin(direction * def::radianConversionFactor));
    qreal cosDirectionAngle = qFabs(qCos(direction * def::radianConversionFactor));
    qreal xOffset = sinDirectionAngle * distance * halfXaxisFactor;
    qreal yOffset = cosDirectionAngle * distance * halfYaxisFactor;

    QPointF offset(xOffset, yOffset);
    return offset;
}

QPointF moveForward(
    const QPointF startPosition,
    int direction,
    int distance)
{
    QPointF endPosition;
    QPointF offset = calculateXYOffset(direction, distance);
    endPosition.setX(startPosition.x() + offset.x());
    endPosition.setY(startPosition.y() + offset.y());

    return endPosition;
}

void rotatePointBasedOnCenterPoint(const QPointF centerPoint,
                                   const int     rotation,
                                   QPointF&      rotatedPoint)
{
    QLineF staticBaseLine(0, 0, 10, 0);
    QLineF rotatedLine(centerPoint, rotatedPoint);
    qreal  rationOffset = staticBaseLine.angleTo(rotatedLine);

    rotatedLine.setAngle(rotation + rationOffset);

    rotatedPoint = rotatedLine.p2();
}

bool isOutOfScene(QPointF pos, QPixmap pixmap)
{
    int x = pos.x();
    int y = pos.y();
    int maxPixmapDimension = std::max(pixmap.width(), pixmap.height());
    int minX = 0 - maxPixmapDimension;
    int maxX = def::sceneWidth + maxPixmapDimension;
    int minY = 0 - maxPixmapDimension;
    int maxY = def::sceneHeight + maxPixmapDimension;
    if(x <= minX || maxX <= x || y <= minY || maxY <= y)
    {
        return true;
    }
    return false;
}

QPixmap getAnimationFrame(QImage* image,
                          int     animFrameXIdx,
                          int     animFrameYIdx,
                          int     animationFrameWidth,
                          int     animationFrameHeight)
{
    QPixmap map;
    map.convertFromImage(image->copy(animFrameXIdx * animationFrameWidth,
                                     animFrameYIdx,
                                     animationFrameWidth,
                                     animationFrameHeight));
    return map;
}
