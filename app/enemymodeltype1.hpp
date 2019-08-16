#ifndef ENEMYMODELTYPE1_HPP
#define ENEMYMODELTYPE1_HPP

#include "enemymodel.hpp"
#include <QPointF>

class EnemyModelType1 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType1(QPointF position,
                    int     health,
                    int     damage,
                    int     moveTimeDelay,
                    int     fireTimeDelay);
    ~EnemyModelType1();

public slots:
    void fire();
    void move();
    void animation();
};

#endif // ENEMYMODELTYPE1_HPP
