#include "enemycontroller.hpp"

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

}
