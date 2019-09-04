#ifndef FIREFUNCTIONS_HPP
#define FIREFUNCTIONS_HPP

#include <QPointF>

typedef void (*fire)(QPointF, int);

void defaultFireFunc(QPointF startPosition, int baseDamage);

void redLevel1FireFunc(QPointF startPosition, int baseDamage);
void redLevel2FireFunc(QPointF startPosition, int baseDamage);
void redLevel3FireFunc(QPointF startPosition, int baseDamage);
void redLevel4FireFunc(QPointF startPosition, int baseDamage);
void redLevel5FireFunc(QPointF startPosition, int baseDamage);

void yellowLevel1FireFunc(QPointF startPosition, int baseDamage);
void yellowLevel2FireFunc(QPointF startPosition, int baseDamage);
void yellowLevel3FireFunc(QPointF startPosition, int baseDamage);
void yellowLevel4FireFunc(QPointF startPosition, int baseDamage);
void yellowLevel5FireFunc(QPointF startPosition, int baseDamage);

void blueLevel1FireFunc(QPointF startPosition, int baseDamage);
void blueLevel2FireFunc(QPointF startPosition, int baseDamage);
void blueLevel3FireFunc(QPointF startPosition, int baseDamage);
void blueLevel4FireFunc(QPointF startPosition, int baseDamage);
void blueLevel5FireFunc(QPointF startPosition, int baseDamage);

#endif // FIREFUNCTIONS_HPP
