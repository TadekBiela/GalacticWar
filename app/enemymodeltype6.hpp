#ifndef ENEMYMODELTYPE6_HPP
#define ENEMYMODELTYPE6_HPP

#include "enemymodel.hpp"
#include "enemyturret.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_rotation_direction {
    left,
    right
};

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
    void rotate();

protected:
    int m_rotationTimeDelay;
    int m_rotationCounter;
    enemy_rotation_direction m_rotationDirection;
    EnemyTurret* m_frontTurret;
};

#endif // ENEMYMODELTYPE6_HPP
