#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "enemyturretdoublecannon.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

EnemyTurretDoubleCannon::EnemyTurretDoubleCannon(
    QGraphicsItem* parent,
    QPointF position,
    int startRotationDegree,
    enemy_turret_rotate_direction rotationDirection
) :
    EnemyTurret(
        parent,
        "enemy_turret",
        position,
        def::enemyTurretDoubleCannonDamage,
        def::enemyTurretDoubleCannonFireTimeDelay,
        startRotationDegree,
        rotationDirection,
        def::enemyTurretDoubleCannonRotateTimeDelay
    ),
    m_fireSideCannon(fire_side_cannon::left)
{

}

EnemyTurretDoubleCannon::~EnemyTurretDoubleCannon() {

}

void EnemyTurretDoubleCannon::fire() {
    const int bulletMoveDirection = (m_rotationDegree + parentItem()->rotation());
    const int pixmapHalfWidth = (pixmap().width() / 2);
    const int bulletPositionOffsetVector = (bulletMoveDirection + 90) % def::maxDegree;

    int pixmapCannonSideXCoordinateOffset = 0;

    if(fire_side_cannon::left == m_fireSideCannon) {
        pixmapCannonSideXCoordinateOffset = pixmapHalfWidth - 7;
        m_fireSideCannon = fire_side_cannon::right;
    }
    else {
        pixmapCannonSideXCoordinateOffset = pixmapHalfWidth + 7;
        m_fireSideCannon = fire_side_cannon::left;
    }

    QPointF bulletPosition = moveForward(
        scenePos(),
        bulletPositionOffsetVector,
        pixmapCannonSideXCoordinateOffset
    );
    BulletModel* bullet = new BulletModel(
        "bullet_enemy8",
        game_object_type::enemy_bullet,
        bulletPosition,
        m_damage,
        bulletMoveDirection,
        def::defaultBulletSpeed
    );
    QGraphicsItem::scene()->addItem(bullet);
}

