#include "playercontroller.hpp"

PlayerController::PlayerController(GeneralView* view)
                                    : m_view(view)
{
    connect(this, SIGNAL(addPlayerToScene(QGraphicsItem*)), view, SLOT(addGameObject(QGraphicsItem*)));
    connect(view, SIGNAL(abortGame()),                      this, SLOT(abortPlayer()));
    m_player = nullptr;
}

PlayerController::~PlayerController()
{

}

void PlayerController::abortPlayer()
{
    m_player = nullptr;
}

void PlayerController::createNewPlayer()
{
    if(m_player != nullptr)
    {
        delete m_player;
    }
    m_player = new PlayerModel;

    connect(this,     SIGNAL(changeAtribute(special_type)), m_player, SLOT(changeAtribute(special_type)));
    connect(m_view,   SIGNAL(mousePressed()),               m_player, SLOT(startFire()));
    connect(m_view,   SIGNAL(mouseReleased()),              m_player, SLOT(stopFire()));
    connect(m_view,   SIGNAL(mouseMoved(QPointF)),          m_player, SLOT(changeMovePosition(QPointF)));
    connect(m_player, SIGNAL(changeHealth(int)),            m_view,   SLOT(updateHealth(int)));
    connect(m_player, SIGNAL(defeated()),                   this,     SLOT(defeated()));

    m_player->start();
    m_player->setFocus();
    m_view->updateHealth(def::maxPlayerHealth);
    emit addPlayerToScene(m_player);
}

void PlayerController::defeated()
{
    delete m_player;
    m_player = nullptr;
    emit playerDefeated();
}

void PlayerController::changePlayerAtribute(special_type reward)
{
    emit changeAtribute(reward);
}
