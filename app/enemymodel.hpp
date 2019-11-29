#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include "gameobject.hpp"
#include <QPointF>
#include <QTimer>
#include <QImage>
#include <QPixmap>

class EnemyModel : public GameObject
{
    Q_OBJECT
public:
    EnemyModel(int     level,
               QPointF position,
               int     health,
               int     damage,
               int     moveTimeDelay,
               int     fireTimeDelay);
    virtual ~EnemyModel();
    void checkCollisions();
    void hit(int damage);
    void destroy();
    int getLevel() const { return m_level; }

signals:
    void destroyed(QPointF position, int level);

public slots:
    virtual void start();
    virtual void stop();
    virtual void fire() = 0;
    virtual void move() = 0;
    virtual void animation();

protected:
    QImage m_image;
    int    m_level;
    int    m_health;
    int    m_damage;
    int    m_direction;
    int    m_animationFrameIdx;
    QTimer m_fireTimer;
    QTimer m_moveTimer;
    QTimer m_animationTimer;
};

#endif // ENEMYMODEL_HPP
