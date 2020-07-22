#include "levelcontroller.hpp"
#include "animationeffectmodel.hpp"
#include "soundeffectmodel.hpp"

LevelController::LevelController(LevelModel*  model,
                                 GeneralView* view)
                                  : m_view(view)
{

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
    QPointF position(def::halfSceneWight,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
//    AnimationEffectModel* levelUpAnim = new AnimationEffectModel("level_up",
//                                                                 position,
//                                                                 def::animationBigFrameWight,
//                                                                 def::animationBigFrameHeight);
    SoundEffectModel* levelUp = new SoundEffectModel("level_up");
//    levelUpAnim->play();
    levelUp->play();
    connect(levelUp, SIGNAL(end()), this, SLOT(changeLevel()));
}

void LevelController::change(EnemyConfiguration newEnemyConfiguration)
{
    emit changeEnemyConfiguration(newEnemyConfiguration);
}
