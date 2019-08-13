#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>

class EnemyModel : public QObject, public QGraphicsPixmapItem
{
public:
    EnemyModel(int     level,
               QPointF position,
               int     health,
               int     damage,
               int     moveTimeDelay,
               int     fireTimeDelay);
    ~EnemyModel();

signals:
    void destroyed(QPointF position, int level);

public slots:
    void fire();
    void move();
    void animation();

protected:
    void hit(int damage);
    void destroy();

    int    m_level;
    int    m_health;
    int    m_damage;
    int    m_animationFrameIdx;
    QTimer m_fireTimer;
    QTimer m_moveTimer;
    QTimer m_animationTimer;
};

#endif // ENEMYMODEL_HPP
