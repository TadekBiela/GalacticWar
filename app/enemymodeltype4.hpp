#ifndef ENEMYMODELTYPE4_HPP
#define ENEMYMODELTYPE4_HPP

#include "enemymodel.hpp"
#include "irandomgenerator.hpp"
#include <QPointF>

class EnemyModelType4 : public EnemyModel
{
    Q_OBJECT
public:
    EnemyModelType4(QPointF position);
    virtual ~EnemyModelType4();

public slots:
    void fire();
    void move();

private:
    int  m_jumpMoveTimeDelay;
    bool m_isJumpMove;
    bool m_jumpSide;
};

#endif // ENEMYMODELTYPE4_HPP
