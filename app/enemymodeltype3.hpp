#ifndef ENEMYMODELTYPE3_HPP
#define ENEMYMODELTYPE3_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum enemy_side
{
    side_left  = -1,
    side_right = 1
};

class EnemyModelType3 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType3(QPointF position);
    virtual ~EnemyModelType3();

public slots:
    void fire();
    void move();

private:
    enemy_side m_fireSide;
    enemy_side m_moveRotationSide;
    int        m_moveSlowFactor;
    bool       m_changeRotateFactor;
    int        m_rotateMinBorder;
    int        m_rotateMaxBorder;

};

#endif // ENEMYMODELTYPE3_HPP
