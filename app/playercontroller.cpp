#include "playercontroller.hpp"

PlayerController::PlayerController(GeneralView* view,
                                   HealthView*  healthView) :
                                   m_view(view),
                                   m_healthView(healthView)
{
    m_player = new PlayerModel;
}

PlayerController::~PlayerController()
{
    if(m_player != nullptr)
    {
        delete m_player;
    }
}

void PlayerController::createNew()
{
    if(m_player != nullptr)
    {
        delete m_player;
    }
    m_player = new PlayerModel;
}

void PlayerController::activate()
{

}

void PlayerController::deactivate()
{

}

void PlayerController::defeated()
{

}

void PlayerController::changePlayerAtribute(special_type reward)
{

}
