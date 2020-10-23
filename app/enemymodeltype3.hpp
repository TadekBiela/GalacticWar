#ifndef ENEMYMODELTYPE3_HPP
#define ENEMYMODELTYPE3_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_fire_side {
    left_cannon,
    right_cannon
};

class EnemyModelType3 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType3(
        QPointF position
    );
    virtual ~EnemyModelType3();

public slots:
    void fire();
    void move();

protected:
    enemy_fire_side m_fireSide;
    enemy_rotation_direction m_moveRotationSide;
    int m_moveSlowFactor;
    int m_rotateMinBorder;
    int m_rotateMaxBorder;
};

#endif // ENEMYMODELTYPE3_HPP
