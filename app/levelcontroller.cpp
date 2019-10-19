#include "levelcontroller.hpp"

LevelController::LevelController(LevelModel* levelModel,
                                 LevelView*  levelView)
{
    connect(this,       SIGNAL(next()),                     levelModel, SLOT(next()));
    connect(levelModel, SIGNAL(update(int)),                levelView,  SLOT(update(int)));
    connect(levelModel, SIGNAL(change(EnemyConfiguration)), this,       SLOT(change(EnemyConfiguration)));
}

void LevelController::nextLevel()
{
    emit next();
}

void LevelController::change(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
