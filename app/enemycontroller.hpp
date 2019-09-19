#ifndef ENEMYCONTROLLER_HPP
#define ENEMYCONTROLLER_HPP

#include "definitions.hpp"
#include "enemyconfiguration.hpp"
#include "generalview.hpp"
#include "irandomgenerator.hpp"
#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>

class EnemyController : public QObject
{
    Q_OBJECT
public:
    EnemyController(GeneralView*      view,
                    IRandomGenerator* generator);
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
    int                m_enemyPercentDistributionTab[def::percentDistTabSize];
    QTimer             m_enemySpawnTimer;
    IRandomGenerator*  m_generator;
};

#endif // ENEMYCONTROLLER_HPP
