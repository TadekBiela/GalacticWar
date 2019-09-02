#ifndef FIREFUNCTIONS_HPP
#define FIREFUNCTIONS_HPP

#include <QPointF>

typedef void (*fire)(QPointF, int);

void defaultFireFunc(QPointF startPosition, int baseDamage);

#endif // FIREFUNCTIONS_HPP
