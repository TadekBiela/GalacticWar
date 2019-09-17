#ifndef ENEMYCONTROLLER_HPP
#define ENEMYCONTROLLER_HPP

#include "enemyconfiguration.hpp"
#include "generalview.hpp"
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>

class EnemyController : public QObject
{
    Q_OBJECT
public:
    EnemyController(GeneralView* view);
    ~EnemyController();

signals:
    void addEnemyToScene(QGraphicsItem* enemy);
    void enemyDestroyed(QPointF position, int enemyLevel);

public slots:
    void changeEnemyConfiguration(EnemyConfiguration newConfiguration);
    void destroyed(QPointF position, int enemyLevel);

protected slots:
    void spawnEnemy();

protected:
    EnemyConfiguration m_currentConfiguration;
    QTimer             m_enemySpawnTimer;
};

#endif // ENEMYCONTROLLER_HPP
