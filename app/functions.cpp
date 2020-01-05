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

bool isOutOfScene(QPointF pos, QPixmap pixmap)
{
    int x = pos.x();
    int y = pos.y();
    int minX = 0 - pixmap.size().width();
    int maxX = def::sceneWight + pixmap.size().width();
    int minY = 0 - pixmap.size().height();
    int maxY = def::sceneHeight + pixmap.size().height();
    if(x < minX || x > maxX || y < minY || y > maxY)
    {
        return true;
    }
    return false;
}

QPixmap getAnimationFrame(QImage* image,
                          int     animFrameIdx,
                          int     animationFrameWidth,
                          int     animationFrameHeight)
{
    QPixmap map;
    map.convertFromImage(image->copy(animFrameIdx * animationFrameWidth,
                                     0,
                                     animationFrameWidth,
                                     animationFrameHeight));
    return map;
}
