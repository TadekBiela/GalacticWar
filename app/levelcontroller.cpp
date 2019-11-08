#include "levelcontroller.hpp"

LevelController::LevelController(LevelModel*  model,
                                 GeneralView* view)
{
    connect(this,  SIGNAL(reset()),                    model, SLOT(reset()));
    connect(this,  SIGNAL(next()),                     model, SLOT(next()));
    connect(model, SIGNAL(update(int)),                view,  SLOT(updateLevel(int)));
    connect(model, SIGNAL(change(EnemyConfiguration)), this,  SLOT(change(EnemyConfiguration)));
}

LevelController::~LevelController()
{

}

void LevelController::resetLevel()
{
    emit reset();
}

void LevelController::nextLevel()
{
    emit next();
}

void LevelController::change(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
