#include "enemymodeltype2.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

EnemyModelType2::EnemyModelType2(
    QPointF position
) :
    EnemyModel(
        def::enemy2Level,
        def::enemy2MaxHealthPoints,
        def::enemy2BaseDamage,
        def::enemy2MoveTimeDelay,
        def::enemy2FireTimeDelay
    ),
    m_rotationDirection(enemy_rotation_direction::left)
{
    m_direction = def::enemy2MinDirectionRange;
    setRotation(m_direction);

    if(position.x() <= def::halfSceneWight) {
        position.setX(position.x() + def::enemy2XCoordinateOffset);
    }
    else {
        position.setX(position.x() - def::enemy2XCoordinateOffset);
    }
    setCenterPosition(position);
}

EnemyModelType2::~EnemyModelType2() {

}

void EnemyModelType2::fire() {
    QPointF position = moveForward(
        getCenterPosition(),
        m_direction,
        def::enemy2FireBulletOffset
    );

    BulletModel* bullet = new BulletModel(
        "bullet_enemy2",
        game_object_type::enemy_bullet,
        position,
        m_damage,
        m_direction,
        def::defaultBulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

void EnemyModelType2::move() {
    changeDirection();
    changeAnimationFrame();

    setPos(moveForward(pos(), m_direction));
    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    checkCollisions();
}

void EnemyModelType2::changeDirection() {
    if(m_direction <= def::enemy2MinDirectionRange) {
        m_rotationDirection = enemy_rotation_direction::left;
    }
    else if(def::enemy2MaxDirectionRange <= m_direction) {
        m_rotationDirection = enemy_rotation_direction::right;
    }

    if(m_rotationDirection == enemy_rotation_direction::left) {
        m_direction++;
    }
    else {
        m_direction--;
    }

    setRotation(m_direction);
}

void EnemyModelType2::changeAnimationFrame() {
    if(170 < m_direction && m_direction < 190) {
        m_animationFrameYIdx = 0;
    }
    else if(190 <= m_direction) {
        m_animationFrameYIdx = 1;
    }
    else {
        m_animationFrameYIdx = 2;
    }
}
