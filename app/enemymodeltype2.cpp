#include "enemymodeltype2.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType2::EnemyModelType2(QPointF position)
    : EnemyModel(2,
                 40,
                 5,
                 30,
                 300),
      m_changeDirectionTime(0),
      m_changeDirectionFactor(false)
{
    m_direction = def::down + 45;
    setRotation(m_direction);

    const int xCoordinateOffset = (position.x() <= def::halfSceneWight) ?
                50 :
                -50;
    position.setX(position.x() + xCoordinateOffset);
    setCenterPosition(position);
}

EnemyModelType2::~EnemyModelType2()
{

}

void EnemyModelType2::fire()
{
    QPointF position = getCenterPosition();
    const int bulletXCoordinateOffsetInPxBasedOnDirection = ((m_direction - 180) * -0.5);
    position.setX(position.x() + bulletXCoordinateOffsetInPxBasedOnDirection);
    const int bulletYCoordinateOffsetInPx = 28;
    position.setY(position.y() + bulletYCoordinateOffsetInPx);
    BulletModel* bullet = new BulletModel("bullet_enemy2",
                                          game_object_type::enemy_bullet,
                                          position,
                                          m_damage,
                                          m_direction,
                                          def::defaultBulletSpeed);
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType2::move()
{
    changeDirection();
    setPos(moveForward(pos(), m_direction));
    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }
    checkCollisions();
}

void EnemyModelType2::changeDirection()
{
    const int changeDirectionStartBorder = 15;
    const int changeDirectionStopBorder  = changeDirectionStartBorder + 18;

    m_changeDirectionTime++;

    if(changeDirectionStartBorder < m_changeDirectionTime && m_changeDirectionTime < changeDirectionStopBorder)
    {
        m_direction = m_direction + (5 * changeBoolToMinusOneOrOne(m_changeDirectionFactor));
    }
    else if(changeDirectionStopBorder <= m_changeDirectionTime)
    {
        m_changeDirectionTime = 0;
        m_changeDirectionFactor = !m_changeDirectionFactor;
    }

    if(170 < m_direction && m_direction < 190)
    {
        m_animationFrameYIdx = 0;
    }
    else if(m_direction <= 190)
    {
        m_animationFrameYIdx = 1;
    }
    else
    {
        m_animationFrameYIdx = 2;
    }
    setRotation(m_direction);
}
