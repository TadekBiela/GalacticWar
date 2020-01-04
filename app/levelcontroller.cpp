#include "levelcontroller.hpp"
#include "soundeffectmodel.hpp"

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

void LevelController::changeLevel()
{
    emit next();
}

void LevelController::nextLevel()
{
    SoundEffectModel* levelUp = new SoundEffectModel("level_up");
    connect(levelUp, SIGNAL(end()), this, SLOT(changeLevel()));
}

void LevelController::change(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
