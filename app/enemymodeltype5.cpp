#include "enemymodeltype5.hpp"
#include "bulletmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QGraphicsScene>

void fireEnemySmallWeapon(QPointF          position,
                           QGraphicsScene* scene);
void fireEnemyMediumWeapon(QPointF         position,
                           QGraphicsScene* scene);
void fireEnemyBigWeapon(QPointF         position,
                        QGraphicsScene* scene);

const fireEnemy EnemyModelType5::s_weapons[enemy_weapon::mode_last_element + 1] =
    { &fireEnemySmallWeapon,
      &fireEnemyMediumWeapon,
      &fireEnemyBigWeapon };

EnemyModelType5::EnemyModelType5(QPointF position)
    : EnemyModel(5,
                 position,
                 500,
                 10,
                 70,
                 1500,
                 def::enemy5AnimationFrameWight,
                 def::enemy5AnimationFrameHeight),
      m_weaponMode(mode_first_element),
      m_changeDirectionTime(def::enemy5ChangeDirectionTimeDelay)
{
    const int positionSideOffset = 40;

    if(position.x() < def::halfSceneWight)
    {
        setPos(QPointF(positionSideOffset,
                       def::enemy5StartYCoordinate));
        m_changeDirectionFactor = true;
    }
    else
    {
        setPos(QPointF((def::sceneWight - pixmap().width() - positionSideOffset),
                       def::enemy5StartYCoordinate));
        m_changeDirectionFactor = false;
    }

    m_direction = def::down;
    setRotation(m_direction);
}

EnemyModelType5::~EnemyModelType5()
{

}

void EnemyModelType5::fire()
{
    s_weapons[m_weaponMode](pos(), QGraphicsItem::scene());

    m_weaponMode = static_cast<enemy_weapon>(m_weaponMode + 1);

    if(enemy_weapon::mode_last_element < m_weaponMode)
    {
        m_weaponMode = enemy_weapon::mode_first_element;
    }
}

void EnemyModelType5::move()
{
    QPointF nextPosition = pos();
    nextPosition.setX(nextPosition.x() +
                      (2 * (changeBoolToMinusOneOrOne(m_changeDirectionFactor))));
    nextPosition.setY(nextPosition.y() + 1);
    setPos(nextPosition);

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
        return;
    }

    m_changeDirectionTime--;
    if(m_changeDirectionTime <= 0)
    {
        m_changeDirectionTime   = def::enemy5ChangeDirectionTimeDelay;
        m_changeDirectionFactor = !m_changeDirectionFactor;
    }

    checkCollisions();
}

void fireEnemySmallWeapon(QPointF         position,
                          QGraphicsScene* scene)
{
    int     weaponXOffset = 22;
    int     weaponYOffset = 32;
    QPointF leftPoint     = position;
    leftPoint.setX(position.x() + weaponXOffset);
    leftPoint.setY(position.y() + def::enemy5AnimationFrameHeight - weaponYOffset);
    BulletModel* bulletLeft = new BulletModel("bullet_enemy5",
                                              game_object_type::enemy_bullet,
                                              leftPoint,
                                              def::enemy5SmallWeaponDamage,
                                              def::down,
                                              def::defaultBulletSpeed + 5);
    scene->addItem(bulletLeft);

    QPointF rightPoint = position;
    rightPoint.setX(position.x() + def::enemy5AnimationFrameWight  - weaponXOffset);
    rightPoint.setY(position.y() + def::enemy5AnimationFrameHeight - weaponYOffset);
    BulletModel* bulletRight = new BulletModel("bullet_enemy5",
                                               game_object_type::enemy_bullet,
                                               rightPoint,
                                               def::enemy5SmallWeaponDamage,
                                               def::down,
                                               def::defaultBulletSpeed + 5);
    scene->addItem(bulletRight);
}

void fireEnemyMediumWeapon(QPointF         position,
                           QGraphicsScene* scene)
{
    int     weaponXOffset = 34;
    int     weaponYOffset = 25;
    QPointF leftPoint     = position;
    leftPoint.setX(position.x() + weaponXOffset);
    leftPoint.setY(position.y() + def::enemy5AnimationFrameHeight - weaponYOffset);
    BulletModel* bulletLeft = new BulletModel("bullet_enemy6",
                                              game_object_type::enemy_bullet,
                                              leftPoint,
                                              def::enemy5MediumWeaponDamage,
                                              def::down,
                                              def::defaultBulletSpeed + 8);
    scene->addItem(bulletLeft);

    QPointF rightPoint = position;
    rightPoint.setX(position.x() + def::enemy5AnimationFrameWight  - weaponXOffset);
    rightPoint.setY(position.y() + def::enemy5AnimationFrameHeight - weaponYOffset);
    BulletModel* bulletRight = new BulletModel("bullet_enemy6",
                                               game_object_type::enemy_bullet,
                                               rightPoint,
                                               def::enemy5MediumWeaponDamage,
                                               def::down,
                                               def::defaultBulletSpeed + 8);
    scene->addItem(bulletRight);
}

void fireEnemyBigWeapon(QPointF         position,
                        QGraphicsScene* scene)
{
    int weaponYOffset = 4;
    position.setX(position.x() + def::enemy5AnimationFrameWight  / 2);
    position.setY(position.y() + def::enemy5AnimationFrameHeight - weaponYOffset);
    BulletModel* bullet = new BulletModel("bullet_enemy7",
                                          game_object_type::enemy_bullet,
                                          position,
                                          def::enemy5BigWeaponDamage,
                                          def::down,
                                          def::defaultBulletSpeed + 12);
    scene->addItem(bullet);
}
