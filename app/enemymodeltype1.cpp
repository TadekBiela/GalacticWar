#include "enemymodeltype1.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType1::EnemyModelType1(QPointF           position,
                                 IRandomGenerator* generator)
    : EnemyModel(1,
                 position,
                 30,
                 10,
                 40,
                 1000)
{
    //If position is on left side of scene enemy fly to down or right, if right side, fly down or left
    int destinationLeftRightFactor = (((def::sceneWight - static_cast<int>(position.x())) / (def::sceneWight / 2)) * 2) - 1; // Can only be -1 or 1
    m_direction = 180 + ((-10 * destinationLeftRightFactor) * generator->bounded(0, 1));//Can only be 190, 180, or 170

    switch (m_direction)
    {
        case 170:
            m_animationFrameYIdx = 1;
            break;
        case 190:
            m_animationFrameYIdx = 2;
    }
    setRotation(m_direction);
}

EnemyModelType1::~EnemyModelType1()
{

}

void EnemyModelType1::fire()
{
    QPointF position = pos();
    position.setX(position.x() + pixmap().size().width() / 2 + ((m_direction - 180) * -0.5));
    position.setY(position.y() + pixmap().size().height() - 5);
    BulletModel* bullet = new BulletModel("bullet_enemy",
                                          game_object_type::enemy_bullet,
                                          position,
                                          m_damage,
                                          m_direction,
                                          def::defaultBulletSpeed);
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType1::move()
{
    setPos(moveForward(pos(), m_direction));
    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }
    checkCollisions();
}
