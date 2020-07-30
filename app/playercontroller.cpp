#include "playercontroller.hpp"
#include "animationeffectmodel.hpp"
#include "soundeffectmodel.hpp"

PlayerController::PlayerController(ControlPlane* controller,
                                   GameplayView* view)
    : m_controller(controller),
      m_model(nullptr)
{
    connect(this, SIGNAL(addPlayerToScene(GameObject*)), view, SLOT(addGameObjectToScene(GameObject*)));
}

PlayerController::~PlayerController()
{

}

void PlayerController::create()
{
    m_model = new PlayerModel;

    connect(m_model,      SIGNAL(addHealthPoints(int)),      this,    SLOT(addHealth(int)));
    connect(m_model,      SIGNAL(subtractHealthPoints(int)), this,    SLOT(subtractHealth(int)));
    connect(m_controller, SIGNAL(mousePressed()),            m_model, SLOT(startFire()));
    connect(m_controller, SIGNAL(mouseReleased()),           m_model, SLOT(stopFire()));
    connect(m_controller, SIGNAL(mouseMoved(QPointF)),       m_model, SLOT(changeMovePosition(QPointF)));

    m_model->setFocus();
    m_model->start();
    emit addPlayerToScene(m_model);
}

void PlayerController::destroy()
{
    QPointF position;
    position.setX(m_model->pos().x() + m_model->pixmap().width()  / 2);
    position.setY(m_model->pos().y() + m_model->pixmap().height() / 2);
    AnimationEffectModel* explosionAnim = new AnimationEffectModel("explosion",
                                                                   position,
                                                                   def::animationFrameWight,
                                                                   def::animationFrameHeight);
    explosionAnim->play();
    SoundEffectModel* explosionSound = new SoundEffectModel("explosion");
    explosionSound->play();

    if(m_model)
    {
        delete m_model;
        m_model = nullptr;
    }
}

void PlayerController::changePlayerAtribute(special_type reward)
{
    m_model->changeAtribute(reward);
}

void PlayerController::addHealth(int healthPoints)
{
    emit addHealthPoints(healthPoints);
}

void PlayerController::subtractHealth(int healthPoints)
{
    emit subtractHealthPoints(healthPoints);
}
