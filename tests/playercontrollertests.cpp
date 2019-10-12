#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/playercontroller.hpp"
#include "../app/playermodel.hpp"
#include "../app/generalview.hpp"
#include "../app/healthview.hpp"
#include "../app/rewardtypes.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(special_type)

class PlayerControllerTest : public PlayerController
{
public:
    PlayerControllerTest(GeneralView* view,
                         HealthView*  healthVodel) :
                         PlayerController(view,
                                          healthVodel) {}
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

TEST_F(PlayerControllerTestsClass, Defeated_CheckIfWillEmitPlayerDefeatedSingal_IsEqual)
{
    GeneralView*         view       = new GeneralView;
    HealthView*          healthView = new HealthView;
    PlayerControllerTest playerController(view, healthView);
    QSignalSpy           signalDefeated(&playerController, &PlayerControllerTest::playerDefeated);
    signalDefeated.wait(utdef::minSignalTimeDelay);

    playerController.defeated();
    int resultSignalCount = signalDefeated.count();

    EXPECT_EQ(resultSignalCount, 1);
    delete healthView;
    delete view;
}

TEST_F(PlayerControllerTestsClass, ChangePlayerAtribute_CheckIfWillEmitChangeAtributeSingal_IsEqual)
{
    qRegisterMetaType<special_type>();
    GeneralView*         view       = new GeneralView;
    HealthView*          healthView = new HealthView;
    PlayerControllerTest playerController(view, healthView);
    QSignalSpy           signalDefeated(&playerController, &PlayerControllerTest::changeAtribute);
    signalDefeated.wait(utdef::minSignalTimeDelay);

    playerController.changePlayerAtribute(special_type::health);
    int          resultSignalCount = signalDefeated.count();
    special_type resultRevardType  = qvariant_cast<special_type>(signalDefeated.takeFirst().at(0));

    EXPECT_EQ(resultSignalCount, 1);
    EXPECT_EQ(resultRevardType,  special_type::health);
    delete healthView;
    delete view;
}
