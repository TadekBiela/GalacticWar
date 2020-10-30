#ifndef ENEMYMODELTYPE6_HPP
#define ENEMYMODELTYPE6_HPP

#include "enemymodel.hpp"
#include "enemyturret.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType6 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType6(
        QPointF position,
        IRandomGenerator* generator
    );
    virtual ~EnemyModelType6();

public slots:
    void start() override;
    void stop() override;

protected slots:
    void fire() override;
    void move() override;

private:
    QPointF getFrontTurretStartPosition();
    QPointF getMiddleTurretStartPosition();
    QPointF getBackTurretStartPosition();
    void rotate();

protected:
    int m_rotationTimeDelay;
    int m_rotationCounter;
    enemy_rotation_direction m_rotationDirection;
    EnemyTurret* m_frontTurret;
    EnemyTurret* m_middleTurret;
    EnemyTurret* m_backTurret;
};

#endif // ENEMYMODELTYPE6_HPP
