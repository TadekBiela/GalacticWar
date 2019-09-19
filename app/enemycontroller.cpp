#include "enemycontroller.hpp"
#include "enemymodeltype1.hpp"
#include "definitions.hpp"

EnemyController::EnemyController(GeneralView*      view,
                                 IRandomGenerator* generator) :
                                 m_generator(generator)
{

}

EnemyController::~EnemyController()
{

}

void EnemyController::changeEnemyConfiguration(EnemyConfiguration newConfiguration)
{
    m_currentConfiguration = newConfiguration;
}

void EnemyController::destroyed(QPointF position, int enemyLevel)
{
    emit enemyDestroyed(position, enemyLevel);
}

void EnemyController::spawnEnemy()
{
    EnemyModel* enemy;
    int enemyType = m_generator->bounded(0, 99);
    QPointF enemyPosition(m_generator->bounded(0, def::sceneWight - def::animationFrameWight),
                          -def::animationFrameHeight);
    switch (enemyType)
    {
        case 1:
            enemy = new EnemyModelType1(enemyPosition, m_generator);
            break;
    }
    emit addEnemyToScene(enemy);
}
