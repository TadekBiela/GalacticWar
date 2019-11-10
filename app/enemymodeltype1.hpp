#ifndef ENEMYMODELTYPE1_HPP
#define ENEMYMODELTYPE1_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType1 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType1(QPointF           position,
                    IRandomGenerator* generator);
    virtual ~EnemyModelType1();

public slots:
    void fire();
    void move();
};

#endif // ENEMYMODELTYPE1_HPP
