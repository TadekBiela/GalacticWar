#include "levelcontroller.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "soundeffectmodel.hpp"

LevelController::LevelController(QWidget* displayWidget)
                                  : m_displayWidget(displayWidget),
                                    m_model(nullptr),
                                    m_view(nullptr)
{

}

LevelController::~LevelController()
{
    if(m_model)
    {
        delete m_model;
    }
    if(m_view)
    {
        delete m_view;
    }
}

void LevelController::create()
{
    m_model = new LevelModel();
    m_view  = new LabelView(m_displayWidget,
                           "levelView");
    m_view->setPosition(def::levelGraphicsPositionX,
                        def::levelGraphicsPositionY);
}

void LevelController::distroy()
{
    delete m_model;
    m_model = nullptr;
    delete m_view;
    m_view = nullptr;
}

void LevelController::show()
{
    m_view->show();
}

void LevelController::hide()
{
    m_view->hide();
}

void LevelController::nextLevel()
{
    QPointF position(def::halfSceneWight,
                     def::halfSceneHeight - def::halfSceneHeight / 4);
    AnimationEffectModel* levelUpAnim = new AnimationEffectModel("level_up",
                                                                 position,
                                                                 def::animationBigFrameWight,
                                                                 def::animationBigFrameHeight);
    levelUpAnim->play();
    SoundEffectModel* levelUp = new SoundEffectModel("level_up");
    levelUp->play();
    m_model->next();
    m_view->set(m_model->getCurrentLevel());
    emit changeEnemyConfig(m_model->getCurrentConfig());
}
