#include "playercontroller.hpp"
#include "animationeffectmodel.hpp"
#include "soundeffectmodel.hpp"

PlayerController::PlayerController(GeneralView* view)
                                    : m_view(view)
{
    connect(this, SIGNAL(addPlayerToScene(QGraphicsItem*)), view, SLOT(addGameObject(QGraphicsItem*)));
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
    emit addPlayerToScene(m_player);
}

void PlayerController::defeated()
{
    QPointF position;
    position.setX(m_player->pos().x() + m_player->pixmap().width()  / 2);
    position.setY(m_player->pos().y() + m_player->pixmap().height() / 2);
//    AnimationEffectModel* explosionAnim = new AnimationEffectModel("explosion",
//                                                                   position,
//                                                                   def::animationFrameWight,
//                                                                   def::animationFrameHeight);
    SoundEffectModel* explosion = new SoundEffectModel("explosion");
//    explosionAnim->play();
    explosion->play();
    m_player->scene()->removeItem(m_player);
    delete m_player;
    m_player = nullptr;
    emit playerDefeated();
}

void PlayerController::changePlayerAtribute(special_type reward)
{
    emit changeAtribute(reward);
}
