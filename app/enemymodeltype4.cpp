#include "enemymodeltype4.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

static QPointF jumpMove(QPointF currentPosition, bool jumpSide)
{
    currentPosition.setX(currentPosition.x()
                         + (5 * changeBoolToMinusOneOrOne(jumpSide)));
    currentPosition.setY(currentPosition.y() + 1);
    return currentPosition;
}

EnemyModelType4::EnemyModelType4(QPointF position)
    : EnemyModel(4,
                 120,
                 20,
                 def::defaultEnemy4MoveTimeDelay,
                 def::defaultEnemy4FireTimeDelay),
      m_jumpMoveTimeDelay(def::defaultEnemyJumpTimeDelay),
      m_isJumpMove(false)
{
    if(position.x() < def::halfSceneWight)
    {
        m_jumpSide = false;
    }
    else
    {
        m_jumpSide = true;
    }

    m_direction = def::down;
    setRotation(m_direction);
    setStartPosition(position);
}

EnemyModelType4::~EnemyModelType4()
{

}

void EnemyModelType4::fire()
{
    QPointF position = pos();
    position.setX(position.x() + pixmap().size().width() / 2);
    position.setY(position.y() + pixmap().size().height() - 20);
    BulletModel* bullet = new BulletModel("bullet_enemy4",
                                          game_object_type::enemy_bullet,
                                          position,
                                          m_damage,
                                          def::down,
                                          def::defaultBulletSpeed - 6);
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType4::move()
{
    m_jumpMoveTimeDelay--;
    if(m_jumpMoveTimeDelay <= 0)
    {
        m_jumpMoveTimeDelay = def::defaultEnemyJumpTimeDelay;
        m_isJumpMove        = !m_isJumpMove;

        if(m_isJumpMove)
        {
            m_jumpSide = !m_jumpSide;
            m_animationFrameYIdx = 1 + (1 * static_cast<int>(m_jumpSide));
            m_fireTimer.setInterval(def::speedupEnemy4FireTimeDelay);
        }
        else
        {
            m_animationFrameYIdx = 0;
            m_fireTimer.setInterval(def::defaultEnemy4FireTimeDelay);
        }
    }
    if(not m_isJumpMove)
    {
        setPos(moveForward(pos(), m_direction));
    }
    else
    {
        setPos(jumpMove(pos(), m_jumpSide));
    }

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }
    checkCollisions();
}
