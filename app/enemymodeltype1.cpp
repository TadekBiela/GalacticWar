#include "enemymodeltype1.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include <QGraphicsScene>

EnemyModelType1::EnemyModelType1(QPointF position) :
                                 EnemyModel(1,
                                            position,
                                            2,
                                            10,
                                            30,
                                            15)
{

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

}

void EnemyModelType1::animation()
{

}
