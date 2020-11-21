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

    connect(
        m_model, SIGNAL(addHealthPoints(int)),
        this, SLOT(addHealth(int))
    );
    connect(
        m_model, SIGNAL(subtractHealthPoints(int)),
        this, SLOT(subtractHealth(int))
    );
    connect(
        m_controller, SIGNAL(startFire()),
        m_model, SLOT(startFire())
    );
    connect(
        m_controller, SIGNAL(stopFire()),
        m_model, SLOT(stopFire())
    );
    connect(
        m_controller, SIGNAL(changeMovePosition(QPointF)),
        m_model, SLOT(changeMovePosition(QPointF))
    );
    connect(
        m_controller, SIGNAL(stopMoveOnAxeX()),
        m_model, SLOT(stopMoveOnAxeX())
    );
    connect(
        m_controller, SIGNAL(stopMoveOnAxeY()),
        m_model, SLOT(stopMoveOnAxeY())
    );
    connect(
        m_model, SIGNAL(getCurrentPosition(QPointF)),
        m_controller, SLOT(setMovePosition(QPointF))
    );

    m_model->setFocus();
    m_model->start();
    emit addPlayerToScene(m_model);
}

void PlayerController::destroy()
{
    QPointF destroyedPlayerPosition = m_model->getCenterPosition();
    AnimationEffectModel* explosionAnim = new AnimationEffectModel("explosion",
                                                                   destroyedPlayerPosition,
                                                                   def::animationFrameWight,
                                                                   def::animationFrameHeight);
    explosionAnim->play();
    SoundEffectModel* explosionSound = new SoundEffectModel("explosion");
    explosionSound->play();

    delete m_model;
    m_model = nullptr;
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
