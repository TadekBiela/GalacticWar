#ifndef ENEMYMODELTYPE6_HPP
#define ENEMYMODELTYPE6_HPP

#include "enemymodel.hpp"
#include "enemyturret.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_rotation_direction
{
    left,
    right
};

class EnemyModelType6 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType6(QPointF position,
                    IRandomGenerator* generator);
    virtual ~EnemyModelType6();

public slots:
    void start() override;
    void stop() override;

private slots:
    void fire();
    void move();
    void startManeuver();
    void rotate();

private:
    void stopManeuver();
    QPointF getFrontTurretStartPosition();

    int m_remainigManeuverTime;
    QTimer m_maneuverTimer;
    bool m_isCarryOutRotationManeuver;
    int m_rotationCounter;
    QTimer m_rotateTimer;
    enemy_rotation_direction m_rotationDirection;
    EnemyTurret* m_frontTurret;
};

#endif // ENEMYMODELTYPE6_HPP
