#include "enemymodeltype1.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

EnemyModelType1::EnemyModelType1(QPointF           position,
                                 IRandomGenerator* generator)
                                  : EnemyModel(1,
                                               position,
                                               2,
                                               10,
                                               80,
                                               1000)
{
    int destinationLeftRightFactor = (((def::sceneWight - static_cast<int>(position.x())) / (def::sceneWight / 2)) * 2) - 1; // Can only be -1 or 1
    //If position is on left side of scene enemy fly to down or right, if right side, fly down or left
    m_direction = 180 + ((-10 * destinationLeftRightFactor) * generator->bounded(0, 1));//Can only be 190, 180, or 170
}

EnemyModelType1::~EnemyModelType1()
{

}

void EnemyModelType1::fire()
{
    BulletModel* bullet = new BulletModel(bullet_type::enemyBullet,
                                          pos(),
                                          m_damage,
                                          def::down,
                                          def::defaultBulletSpeed);
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType1::move()
{
    setPos(moveForward(pos(), m_direction));
    checkCollisions();
}

void EnemyModelType1::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }
}
