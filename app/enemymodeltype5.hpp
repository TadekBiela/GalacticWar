#ifndef ENEMYMODELTYPE5_HPP
#define ENEMYMODELTYPE5_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum enemy_weapon
{
    mode_first_element = 0,
    mode_small         = 0,
    mode_medium        = 1,
    mode_big           = 2,
    mode_last_element  = 2
};

typedef void (*fireEnemy)(QPointF position, QGraphicsScene* scene);

class EnemyModelType5 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType5(QPointF position);
    virtual ~EnemyModelType5();

public slots:
    void fire();
    void move();

private:
    const static fireEnemy s_weapons[enemy_weapon::mode_last_element + 1];

    enemy_weapon m_weaponMode;
    int          m_changeDirectionTime;
    bool         m_changeDirectionFactor;
};

#endif // ENEMYMODELTYPE5_HPP
