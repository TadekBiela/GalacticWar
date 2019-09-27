#include "levelcontroller.hpp"

LevelController::LevelController(LevelModel* levelModel,
                                 LevelView*  levelView)
{

}

void LevelController::nextLevel()
{
    emit nextLevelInModel();
}

void LevelController::updateLevelView(int value)
{

}

void LevelController::changeEnemyConfig(EnemyConfiguration newEnemyConfiguration)
{

}
