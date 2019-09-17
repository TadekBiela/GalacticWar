#include "enemycontroller.hpp"

EnemyController::EnemyController(GeneralView* view)
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
