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
