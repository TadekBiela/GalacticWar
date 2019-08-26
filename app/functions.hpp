#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <QPointF>

//Changes false into -1 and true to 1
inline int changeBoolToMinusOneOrOne(bool value);

QPointF calculateXYOffset(int direction);

QPointF moveForward(const QPointF startPosition, int direction);

#endif // FUNCTIONS_HPP
