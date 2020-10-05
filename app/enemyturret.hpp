#ifndef ENEMYTURRET_HPP
#define ENEMYTURRET_HPP

#include "firefunctions.hpp"
#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>

enum class enemy_turret_type {
    double_cannons = 1,
    triple_cannons = 2
};

enum class enemy_turret_rotate_direction {
    left = -1,
    right = 1
};

class EnemyTurret : public GameObject
{
    Q_OBJECT
public:
    EnemyTurret(
        QGraphicsItem* parent,
        enemy_turret_type type,
        QPointF position,
        int damage,
        int fireTimeDelay,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection,
        int rotateTimeDelay
    );
    virtual ~EnemyTurret();

public slots:
    void start() override;
    void stop() override;

protected slots:
    void fire();
    void rotate();

protected:
    int m_damage;
    fireEnemyTurret fireTurret;
    QTimer m_fireTimer;
    enemy_turret_rotate_direction m_rotationDirection;
    int m_rotationDegree;
    int m_maxRotationDegree;
    QTimer m_rotateTimer;
};

#endif // ENEMYTURRET_HPP
