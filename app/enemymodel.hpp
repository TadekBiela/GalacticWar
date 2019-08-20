#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>

class EnemyModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyModel(int     level,
               QPointF position,
               int     health,
               int     damage,
               int     moveTimeDelay,
               int     fireTimeDelay);
    ~EnemyModel();
    void hit(int damage);
    void destroy();

signals:
    void destroyed(QPointF position, int level);

public slots:
    virtual void start();
    virtual void stop();
    virtual void fire() = 0;
    virtual void move() = 0;
    virtual void animation() = 0;

protected:
    int    m_level;
    int    m_health;
    int    m_damage;
    int    m_animationFrameIdx;
    QTimer m_fireTimer;
    QTimer m_moveTimer;
    QTimer m_animationTimer;
};

#endif // ENEMYMODEL_HPP
