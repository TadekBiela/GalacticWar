#include "enemymodeltype3.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

EnemyModelType3::EnemyModelType3(
    QPointF position
) :
    EnemyModel(
        def::enemy3Level,
        def::enemy3MaxHealthPoints,
        def::enemy3BaseDamage,
        def::enemy3MoveTimeDelay,
        def::enemy3FireTimeDelay
    ),
    m_fireSide(enemy_fire_side::right_cannon),
    m_moveSlowFactor(def::enemy3MoveSlowFactor)
{
    int positionSideOffset = def::animationFrameWight;

    if(position.x() < def::halfSceneWight) {
        setCenterPosition(positionSideOffset, position.y());
        m_moveRotationSide = enemy_rotation_direction::left;
        m_rotateMinBorder = def::enemy3RotateLeftSideMinBorder;
        m_rotateMaxBorder = def::enemy3RotateLeftSideMaxBorder;
    }
    else {
        setCenterPosition((def::sceneWight - positionSideOffset), position.y());
        m_moveRotationSide = enemy_rotation_direction::right;
        m_rotateMinBorder = def::enemy3RotateRightSideMinBorder;
        m_rotateMaxBorder = def::enemy3RotateRightSideMaxBorder;
    }

    m_direction = def::down;
    setRotation(m_direction);
}

EnemyModelType3::~EnemyModelType3() {

}

void EnemyModelType3::fire() {
    int bulletPositionOffsetDirection = 0;;
    if(enemy_fire_side::left_cannon == m_fireSide) {
        m_fireSide = enemy_fire_side::right_cannon;
        bulletPositionOffsetDirection = m_direction + 90;
    }
    else {
        m_fireSide = enemy_fire_side::left_cannon;
        bulletPositionOffsetDirection = m_direction - 90;
    }

    QPointF enemyPosition = getCenterPosition();
    QPointF bulletPosition = moveForward(
        enemyPosition,
        bulletPositionOffsetDirection,
        def::enemy3FireSideOffset
    );

    BulletModel* bullet = new BulletModel(
        "bullet_enemy3",
        game_object_type::enemy_bullet,
        bulletPosition,
        m_damage,
        m_direction,
        def::enemy3BulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType3::move() {
    QPointF moveNextPosition = pos();
    moveNextPosition.setY(moveNextPosition.y() + m_moveSlowFactor);
    setPos(moveNextPosition);

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    if(def::enemy3MinMoveSlowFactor < m_moveSlowFactor) {
        m_moveSlowFactor--;
    }

    if(enemy_rotation_direction::left == m_moveRotationSide) {
        m_direction -= def::enemy3RotateAngle;
        if(m_direction <= m_rotateMinBorder) {
            m_moveRotationSide = enemy_rotation_direction::right;
            m_animationFrameYIdx = 1;
        }
    }
    else {
        m_direction += def::enemy3RotateAngle;
        if(m_rotateMaxBorder <= m_direction) {
            m_moveRotationSide = enemy_rotation_direction::left;
            m_animationFrameYIdx = 2;
        }
    }
    setRotation(m_direction);

    checkCollisions();
}
