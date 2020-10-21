#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include "definitions.hpp"
#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>
#include <QImage>
#include <QPixmap>

enum class enemy_rotation_direction {
    left,
    right
};

class EnemyModel : public GameObject
{
    Q_OBJECT
public:
    EnemyModel(int level,
               int health,
               int damage,
               int moveTimeDelay,
               int fireTimeDelay,
               int animationFrameWidth  = def::animationFrameWight,
               int animationFrameHeight = def::animationFrameHeight);
    virtual ~EnemyModel();
    void destroy();
    int getLevel() const { return m_level; }

signals:
    void destroyed(QPointF position, int level);

public slots:
    virtual void start();
    virtual void stop();

protected slots:
    virtual void fire() = 0;
    virtual void move() = 0;
    virtual void animation();

protected:
    void checkCollisions();
    void hit(int damage);

    QImage* m_image;
    int m_level;
    int m_health;
    int m_damage;
    int m_direction;
    int m_animationFrameXIdx;
    int m_animationFrameYIdx;
    QTimer m_fireTimer;
    QTimer m_moveTimer;
    QTimer m_animationTimer;
};

#endif // ENEMYMODEL_HPP
