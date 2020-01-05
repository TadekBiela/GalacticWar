#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <QPointF>
#include <QPixmap>
#include <QImage>

//Changes false into -1 and true to 1
inline int changeBoolToMinusOneOrOne(bool value);

QPointF calculateXYOffset(int direction);

QPointF moveForward(const QPointF startPosition, int direction);

bool isOutOfScene(QPointF pos, QPixmap pixmap);

QPixmap getAnimationFrame(QImage* image,
                          int     animFrameIdx,
                          int     animationFrameWidth,
                          int     animationFrameHeight);

#endif // FUNCTIONS_HPP
