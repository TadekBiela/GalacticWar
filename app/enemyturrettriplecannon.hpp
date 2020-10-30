#ifndef ENEMYTURRETTRIPLECANNON_HPP
#define ENEMYTURRETTRIPLECANNON_HPP

#include "definitions.hpp"
#include "enemyturret.hpp"
#include <QGraphicsItem>
#include <QPointF>

class EnemyTurretTripleCannon : public EnemyTurret
{
    Q_OBJECT
public:
    EnemyTurretTripleCannon(
        QGraphicsItem* parent,
        QPointF position,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection
    );
    virtual ~EnemyTurretTripleCannon();

protected slots:
    void fire();

protected:
    static const int s_fireCannonOffsets[def::enemyTurretTripleCannonMaxFireCannonOffsets];
    int m_currentFireCannonIdx;
};

#endif // ENEMYTURRETTRIPLECANNON_HPP
