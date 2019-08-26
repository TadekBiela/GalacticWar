#include "functions.hpp"
#include "definitions.hpp"
#include <QtMath>

//Changes false into -1 and true to 1
int changeBoolToMinusOneOrOne(bool value)
{
    return (static_cast<int>(value) * 2 - 1);
}

QPointF calculateXYOffset(int direction)
{
    int halfXaxisFactor = changeBoolToMinusOneOrOne(static_cast<bool>(direction / 180)) * -1;
    int halfYaxisFactor = changeBoolToMinusOneOrOne(static_cast<bool>(((direction / 90) % 3)));
    qreal sinDirectionAngle = qFabs(qSin(direction * def::radianConversionFactor));
    qreal cosDirectionAngle = qFabs(qCos(direction * def::radianConversionFactor));
    qreal xOffset = sinDirectionAngle * def::moveVectorLength * halfXaxisFactor;
    qreal yOffset = cosDirectionAngle * def::moveVectorLength * halfYaxisFactor;

    QPointF offset(xOffset, yOffset);
    return offset;
}

QPointF moveForward(const QPointF startPosition, int direction)
{
    QPointF endPosition;
    QPointF offset = calculateXYOffset(direction);
    endPosition.setX(startPosition.x() + offset.x());
    endPosition.setY(startPosition.y() + offset.y());

    return endPosition;
}
