#include "playercontroller.hpp"

PlayerController::PlayerController(GeneralView* view,
                                   HealthView*  healthView)
                                    : m_view(view),
                                      m_healthView(healthView)
{
    connect(this, SIGNAL(addPlayerToScene(QGraphicsItem*)), view, SLOT(addGameObject(QGraphicsItem*)));
    m_player = nullptr;
}

PlayerController::~PlayerController()
{

}

void PlayerController::createNew()
{
    if(m_player != nullptr)
    {
        delete m_player;
    }
    m_player = new PlayerModel;

    connect(this,     SIGNAL(changeAtribute(special_type)), m_player,     SLOT(changeAtribute(special_type)));
    connect(m_view,   SIGNAL(mousePressed()),               m_player,     SLOT(startFire()));
    connect(m_view,   SIGNAL(mouseReleased()),              m_player,     SLOT(stopFire()));
    connect(m_view,   SIGNAL(mouseMoved(QPointF)),          m_player,     SLOT(changeDirection(QPointF)));
    connect(m_player, SIGNAL(changeHealth(int)),            m_healthView, SLOT(update(int)));

    emit addPlayerToScene(m_player);
}

void PlayerController::defeated()
{
    emit playerDefeated();
}

void PlayerController::changePlayerAtribute(special_type reward)
{
    emit changeAtribute(reward);
}
