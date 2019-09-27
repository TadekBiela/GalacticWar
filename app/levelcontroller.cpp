#include "levelcontroller.hpp"

LevelController::LevelController(LevelModel* levelModel,
                                 LevelView*  levelView)
{
    connect(levelModel, SIGNAL(updateLevelView(int)), levelView, SLOT(update(int)));
}

void LevelController::nextLevel()
{
    emit nextLevelInModel();
}

void LevelController::changeEnemyConfig(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
