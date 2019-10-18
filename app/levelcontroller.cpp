#include "levelcontroller.hpp"

LevelController::LevelController(LevelModel* levelModel,
                                 LevelView*  levelView)
{
    connect(levelModel, SIGNAL(update(int)), levelView,  SLOT(update(int)));
    connect(this,       SIGNAL(next()),      levelModel, SLOT(next()));
    connect(levelModel, SIGNAL(change(EnemyConfiguration newEnemyConfiguration)),
            this,       SLOT(change(EnemyConfiguration newEnemyConfiguration)));
}

void LevelController::nextLevel()
{
    emit next();
}

void LevelController::change(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
