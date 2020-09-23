#include "enemymodeltype3.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType3::EnemyModelType3(QPointF position)
    : EnemyModel(3,
                 100,
                 8,
                 20,
                 200),
      m_moveSlowFactor(25)
{
    int positionSideOffset = def::animationFrameWight;
    int rotateBorderOffset = 60;

    if(position.x() < def::halfSceneWight)
    {
        setCenterPosition(positionSideOffset, position.y());
        m_moveRotationSide   = enemy_side::side_left;
        m_rotateMinBorder    = def::up + rotateBorderOffset;
        m_rotateMaxBorder    = def::down;
        m_changeRotateFactor = false;
    }
    else
    {
        setCenterPosition((def::sceneWight - positionSideOffset), position.y());
        m_moveRotationSide   = enemy_side::side_right;
        m_rotateMinBorder    = def::down;
        m_rotateMaxBorder    = 360 - rotateBorderOffset;
        m_changeRotateFactor = true;
    }

    m_direction = def::down;
    setRotation(m_direction);
}

EnemyModelType3::~EnemyModelType3()
{

}

void EnemyModelType3::fire()
{
    QPointF centerPoint = getCenterPosition();
    int     fireSideOffset = 14 * m_fireSide;
    QPointF sidePoint      = centerPoint;
    sidePoint.setX(sidePoint.x()
                   + fireSideOffset);
    rotatePointBasedOnCenterPoint(centerPoint,
                                  m_direction * -1,
                                  sidePoint);

    BulletModel* bullet = new BulletModel("bullet_enemy3",
                                          game_object_type::enemy_bullet,
                                          sidePoint,
                                          m_damage,
                                          m_direction,
                                          def::defaultBulletSpeed - 5);
    QGraphicsItem::scene()->addItem(bullet);

    if(enemy_side::side_left == m_fireSide)
    {
        m_fireSide = enemy_side::side_right;
    }
    else
    {
        m_fireSide = enemy_side::side_left;
    }
}

void EnemyModelType3::move()
{
    const int rotateAngle      = 3;
    QPointF   moveNextPosition = pos();
    moveNextPosition.setY(moveNextPosition.y() + m_moveSlowFactor);
    setPos(moveNextPosition);

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }

    m_direction += (rotateAngle * changeBoolToMinusOneOrOne(m_changeRotateFactor));

    if(m_direction <= m_rotateMinBorder || m_rotateMaxBorder <= m_direction)
    {
        m_changeRotateFactor = !m_changeRotateFactor;
    }

    if(rotateAngle < m_moveSlowFactor)
    {
        m_moveSlowFactor--;
    }

    m_animationFrameYIdx = 1 + static_cast<int>(m_changeRotateFactor);
    setRotation(m_direction);
    checkCollisions();
}
