#include "definitions.hpp"
#include "enemyturret.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include <QPixmap>

EnemyTurret::EnemyTurret(
    QGraphicsItem* parent,
    QString graphicsName,
    QPointF position,
    int damage,
    int fireTimeDelay,
    int startRotationDegree,
    enemy_turret_rotate_direction rotationDirection,
    int rotateTimeDelay
) :
    GameObject(game_object_type::enemy_turret),
    m_damage(damage),
    m_rotationDirection(rotationDirection),
    m_rotationDegree(startRotationDegree * static_cast<int>(m_rotationDirection)),
    m_maxRotationDegree(
        m_rotationDegree +
        (def::enemyTurretRotationDegreeRange * static_cast<int>(m_rotationDirection))
    )
{
    setParentItem(parent);
    QPixmap map;
    map.convertFromImage(*g_imageStorage->getImage(graphicsName));
    setPixmap(map);

    setTransformOriginPoint(
        (pixmap().width() / 2),
        (pixmap().height() / 2) + def::enemyTurretPixmapCenterPointHightOffset
    );

    setCenterPosition(position);

    setRotation(m_rotationDegree);

    connect(
        &m_fireTimer,
        SIGNAL(timeout()),
        this,
        SLOT(fire())
    );
    m_fireTimer.setInterval(fireTimeDelay);

    connect(
        &m_rotateTimer,
        SIGNAL(timeout()),
        this,
        SLOT(rotate())
    );
    m_rotateTimer.setInterval(rotateTimeDelay);
}

EnemyTurret::~EnemyTurret() {

}

void EnemyTurret::start() {
    m_fireTimer.start();
    m_rotateTimer.start();
}

void EnemyTurret::stop() {
    m_fireTimer.stop();
    m_rotateTimer.stop();
}

void EnemyTurret::rotate() {
    m_rotationDegree += static_cast<int>(m_rotationDirection);
    if(m_rotationDegree == m_maxRotationDegree) {
        if(enemy_turret_rotate_direction::left == m_rotationDirection) {
            m_rotationDirection = enemy_turret_rotate_direction::right;
        }
        else {
            m_rotationDirection = enemy_turret_rotate_direction::left;
        }
        m_maxRotationDegree += (def::enemyTurretRotationDegreeRange * static_cast<int>(m_rotationDirection));
    }
    setRotation(m_rotationDegree);
}

