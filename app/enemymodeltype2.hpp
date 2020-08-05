#ifndef ENEMYMODELTYPE2_HPP
#define ENEMYMODELTYPE2_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType2 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType2(QPointF position);
    virtual ~EnemyModelType2();

public slots:
    void fire();
    void move();

private:
    void changeDirection();
    int  m_changeDirectionTime;
    bool m_changeDirectionFactor;
};

#endif // ENEMYMODELTYPE2_HPP
