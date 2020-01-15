#include "firefunctions.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"

void defaultFireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{
    BulletModel* bullet = new BulletModel("bullet_default",
                                          startPosition,
                                          baseDamage,
                                          def::up,
                                          def::defaultBulletSpeed);
    scene->addItem(bullet);
}

void redLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void redLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void redLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void redLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void redLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void yellowLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel1FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel2FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel3FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel4FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}

void blueLevel5FireFunc(QGraphicsScene* scene, QPointF startPosition, int baseDamage)
{

}
