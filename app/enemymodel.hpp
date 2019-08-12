#ifndef ENEMYMODEL_HPP
#define ENEMYMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include <QMediaPlayer>

class EnemyModel : public QObject, public QGraphicsPixmapItem
{
public:
    EnemyModel(int level,
               int health,
               int damage,
               int moveTimeDelay,
               int fireTimeDelay);
    ~EnemyModel();

signals:
    void destroyed(QPointF position, int level);

public slots:
    void fire();
    void move();
    void animation();
    void destroy();

protected:
    void hit(int damage);

    int          m_level;
    int          m_health;
    int          m_damage;
    int          m_moveTimeDelay;
    int          m_fireTimeDelay;
    int          m_animationTime;
    int          m_animationFrameIdx;
    int          m_destroyTime;
    QTimer       m_fireTimer;
    QTimer       m_moveTimer;
    QTimer       m_animationTimer;
    QTimer       m_destroyTimer;
    QMediaPlayer m_destroySound;
};

#endif // ENEMYMODEL_HPP
