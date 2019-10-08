#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/playercontroller.hpp"
#include "../app/playermodel.hpp"
#include "../app/generalview.hpp"
#include "../app/healthview.hpp"
#include <QTimer>
#include <QDebug>
class PlayerModelMock : public PlayerModel
{
public:
    PlayerModelMock() {}

    void setHealth(int health) { m_health = health; }
    int           getHealth()    const { return m_health; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }
    const QTimer& getFireTimer() const { return m_fireTimer; }

//    bool   m_isMoving;
//    int    m_direction;
//    int    m_health;
//    weapon m_weapon;
//    int    m_weaponTier;
//    int    m_moveTimeDelay;
//    QTimer m_moveTimer;
//    QTimer m_fireTimer;
};

class PlayerControllerTest : public PlayerController
{
public:
    PlayerControllerTest(GeneralView* view,
                         HealthView*  healthVodel) :
                         PlayerController(view,
                                          healthVodel) {}
    PlayerControllerTest(GeneralView*     view,
                         HealthView*      healthVodel,
                         PlayerModelMock* playerMock) :
                         PlayerController(view,
                                          healthVodel)
    {
        delete m_player;
        m_player = playerMock;
    }
    PlayerModel* getPlayerModel() { return m_player; }
    void defeat()
    {
        delete m_player;
        m_player = nullptr;
    }
};

class PlayerControllerTestsClass : public testing::Test
{
};

TEST_F(PlayerControllerTestsClass, CreateNew_CheckIfWillCreateNewPlayerWhenOldPlayerWasDefeated_IsEqual)
{
    GeneralView*         view       = new GeneralView;
    HealthView*          healthView = new HealthView;
    PlayerControllerTest playerController(view, healthView);
    playerController.defeat();

    playerController.createNew();
    PlayerModel* resultPlayer = playerController.getPlayerModel();

    EXPECT_TRUE(resultPlayer != nullptr);
    delete healthView;
    delete view;
}

TEST_F(PlayerControllerTestsClass, CreateNew_CheckIfWillCreateNewPlayerWhenOldPlayerIsStillAlive_IsEqual)
{
    GeneralView*         view       = new GeneralView;
    HealthView*          healthView = new HealthView;
    PlayerControllerTest playerController(view, healthView);
    PlayerModel*         oldPlayer  = playerController.getPlayerModel();
    oldPlayer->setHealth(500);

    playerController.createNew();
    PlayerModel* resultPlayer       = playerController.getPlayerModel();
    int          resultPlayerHealth = resultPlayer->getHealth();

    EXPECT_EQ(resultPlayerHealth, def::maxPlayerHealth);
    delete healthView;
    delete view;
}

TEST_F(PlayerControllerTestsClass, Activate_CheckIfPlayerModelWillActiveAllTimersAndSignalsWillBeNotBlocked_IsEqual)
{
    GeneralView*         view       = new GeneralView;
    HealthView*          healthView = new HealthView;
    PlayerModelMock*     playerMock = new PlayerModelMock;
    PlayerControllerTest playerController(view, healthView, playerMock);


    playerController.activate();
    PlayerModelMock* resultPlayer         = dynamic_cast<PlayerModelMock*>(playerController.getPlayerModel());
    bool             resultIsSlotBlocked  = resultPlayer->signalsBlocked();
    bool             resultMoveTimerActiv = resultPlayer->getMoveTimer().isActive();
    bool             resultFireTimerActiv = resultPlayer->getFireTimer().isActive();

    EXPECT_FALSE(resultIsSlotBlocked);
    EXPECT_TRUE(resultMoveTimerActiv);
    EXPECT_TRUE(resultFireTimerActiv);
    delete healthView;
    delete view;
}
