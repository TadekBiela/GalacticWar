#ifndef ENEMYMODELTYPE4_HPP
#define ENEMYMODELTYPE4_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

enum class enemy_jump_side {
    left,
    right
};

class EnemyModelType4 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType4(
        QPointF position
    );
    virtual ~EnemyModelType4();

public slots:
    void fire();
    void move();

private:
    void jumpMove();

protected:
    int m_jumpMoveTimeDelay;
    bool m_isJumpMove;
    enemy_jump_side m_jumpSide;
};

#endif // ENEMYMODELTYPE4_HPP
