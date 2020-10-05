#ifndef FIREFUNCTIONS_HPP
#define FIREFUNCTIONS_HPP

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


typedef void (*fireEnemyTurret)(
    QGraphicsScene* scene,
    QPointF centerPoint,
    QPixmap pixmap,
    int bulletMoveDirection,
    int baseDamage
);

void doubleCannonTurretFireFunc(
    QGraphicsScene* scene,
    QPointF centerPoint,
    QPixmap pixmap,
    int bulletMoveDirection,
    int baseDamage
);

void tripleCannonTurretFireFunc(
    QGraphicsScene* scene,
    QPointF centerPoint,
    QPixmap pixmap,
    int bulletMoveDirection,
    int baseDamage
);

#endif // FIREFUNCTIONS_HPP
