#ifndef ENEMYCONTROLLER_HPP
#define ENEMYCONTROLLER_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"
#include "gameobject.hpp"
#include "gameplayview.hpp"
#include "irandomgenerator.hpp"
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>

class EnemyController : public QObject
{
    Q_OBJECT
public:
    EnemyController(
        GameplayView* view
    );
    virtual ~EnemyController();

signals:
    void addEnemyToScene(
        GameObject* enemy
    );
    void enemyDestroyed(
        QPointF position,
        int enemyLevel
    );

public slots:
    void changeEnemyConfig(
        EnemyConfiguration newEnemyConfig
    );
    void destroyed(
        QPointF position,
        int enemyLevel
    );
    void startSpawning();
    void stopSpawning();

protected slots:
    void spawnEnemy();

protected:
    int m_enemyPercentDistributionTab[def::percentDistTabSize];
    int m_minEnemySpawnTimeDelay;
    int m_maxEnemySpawnTimeDelay;
    QTimer m_enemySpawnTimer;
    int m_remainigSpawnTime;
    IRandomGenerator* m_generator;
};

#endif // ENEMYCONTROLLER_HPP
