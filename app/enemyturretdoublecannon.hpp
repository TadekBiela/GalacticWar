#ifndef ENEMYTURRETDOUBLECANNON_HPP
#define ENEMYTURRETDOUBLECANNON_HPP

#include "enemyturret.hpp"
#include <QGraphicsItem>
#include <QPointF>

enum class fire_side_cannon {
    left,
    right
};

class EnemyTurretDoubleCannon : public EnemyTurret
{
    Q_OBJECT
public:
    EnemyTurretDoubleCannon(
        QGraphicsItem* parent,
        QPointF position,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection
    );
    virtual ~EnemyTurretDoubleCannon();

protected slots:
    void fire();

protected:
    fire_side_cannon m_fireSideCannon;
};

#endif // ENEMYTURRETDOUBLECANNON_HPP
