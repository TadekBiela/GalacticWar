#include "enemymodeltype5.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

void fireEnemySmallWeapon(
    QPointF position,
    QGraphicsScene* scene
);
void fireEnemyMediumWeapon(
    QPointF position,
    QGraphicsScene* scene
);
void fireEnemyBigWeapon(
    QPointF position,
    QGraphicsScene* scene
);

const fireEnemy EnemyModelType5::s_weapons[enemy_weapon::mode_last_element + 1] = {
    &fireEnemySmallWeapon,
    &fireEnemyMediumWeapon,
    &fireEnemyBigWeapon
};

EnemyModelType5::EnemyModelType5(
QPointF position
) : 
    EnemyModel(
        def::enemy5Level,
        def::enemy5MaxHealthPoints,
        def::enemy5BaseDamage,
        def::enemy5MoveTimeDelay,
        def::enemy5FireTimeDelay,
        def::enemy5AnimationFrameWight,
        def::enemy5AnimationFrameHeight
    ),
    m_weaponMode(mode_first_element),
    m_changeMoveSideTimeDelay(def::enemy5ChangeMoveSideTimeDelay)
{
    if(position.x() <= def::halfSceneWight) {
        setCenterPosition(
            def::enemy5StartXCoordinate,
            def::enemy5StartYCoordinate
        );
        m_moveSide = enemy_move_side::right;
    }
    else {
        setCenterPosition(
            def::sceneWight - def::enemy5StartXCoordinate,
            def::enemy5StartYCoordinate
        );
        m_moveSide = enemy_move_side::left;
    }

    m_direction = def::down;
    setRotation(m_direction);
}

EnemyModelType5::~EnemyModelType5() {

}

void EnemyModelType5::fire() {
    s_weapons[m_weaponMode](
        getCenterPosition(),
        QGraphicsItem::scene()
    );

    m_weaponMode = static_cast<enemy_weapon>(m_weaponMode + 1);

    if(enemy_weapon::mode_last_element < m_weaponMode){
        m_weaponMode = enemy_weapon::mode_first_element;
    }
}

void EnemyModelType5::move() {
    QPointF nextPosition = getCenterPosition();
    if(enemy_move_side::right == m_moveSide) {
        nextPosition.rx() += def::enemy5XCoordinateOffsetInPx;
    }
    else {
        nextPosition.rx() -= def::enemy5XCoordinateOffsetInPx;
    }
    nextPosition.ry() += def::enemy5YCoordinateOffsetInPx;
    setCenterPosition(nextPosition);

    if(isOutOfScene(pos(), pixmap())) {
        delete this;
        return;
    }

    changeMoveSide();

    checkCollisions();
}

void EnemyModelType5::changeMoveSide() {
    m_changeMoveSideTimeDelay--;
    if(m_changeMoveSideTimeDelay <= 0) {
        m_changeMoveSideTimeDelay = def::enemy5ChangeMoveSideTimeDelay;

        if(enemy_move_side::right == m_moveSide) {
            m_moveSide = enemy_move_side::left;
        }
        else {
            m_moveSide = enemy_move_side::right;
        }
    }
}

void fireEnemySmallWeapon(
    QPointF position,
    QGraphicsScene* scene
) {
    QPointF leftPosition = position;
    leftPosition.rx() -= def::enemy5SmallWeaponXOffset;
    BulletModel* bulletLeft = new BulletModel(
        "bullet_enemy5",
        game_object_type::enemy_bullet,
        leftPosition,
        def::enemy5SmallWeaponDamage,
        def::down,
        def::enemy5SmallWeaponBulletMoveTimeDelay
    );
    scene->addItem(bulletLeft);

    QPointF rightPosition = position;
    rightPosition.rx() += def::enemy5SmallWeaponXOffset;
    BulletModel* bulletRight = new BulletModel(
        "bullet_enemy5",
        game_object_type::enemy_bullet,
        rightPosition,
        def::enemy5SmallWeaponDamage,
        def::down,
        def::enemy5SmallWeaponBulletMoveTimeDelay
    );
    scene->addItem(bulletRight);
}

void fireEnemyMediumWeapon(
    QPointF position,
    QGraphicsScene* scene
) {
    QPointF leftPosition = position;
    leftPosition.rx() -= def::enemy5MediumWeaponXOffset;
    BulletModel* bulletLeft = new BulletModel(
         "bullet_enemy6",
         game_object_type::enemy_bullet,
         leftPosition,
         def::enemy5MediumWeaponDamage,
         def::down,
         def::enemy5MediumWeaponBulletMoveTimeDelay
    );
    scene->addItem(bulletLeft);

    QPointF rightPosition = position;
    rightPosition.rx() += def::enemy5MediumWeaponXOffset;
    BulletModel* bulletRight = new BulletModel(
        "bullet_enemy6",
        game_object_type::enemy_bullet,
        rightPosition,
        def::enemy5MediumWeaponDamage,
        def::down,
        def::enemy5MediumWeaponBulletMoveTimeDelay
    );
    scene->addItem(bulletRight);
}

void fireEnemyBigWeapon(
    QPointF position,
    QGraphicsScene* scene
) {
    QPointF bulletPosition = position;
    bulletPosition.ry() += def::enemy5BigWeaponYOffset;
    BulletModel* bullet = new BulletModel(
        "bullet_enemy7",
        game_object_type::enemy_bullet,
        bulletPosition,
        def::enemy5BigWeaponDamage,
        def::down,
        def::enemy5BigWeaponBulletMoveTimeDelay
    );
    scene->addItem(bullet);
}
