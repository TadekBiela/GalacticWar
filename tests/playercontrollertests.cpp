#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/playercontroller.hpp"
#include "../app/playermodel.hpp"
#include "../app/generalview.hpp"
#include "../app/rewardtypes.hpp"
#include <QSignalSpy>

//Q_DECLARE_METATYPE(special_type)

//class PlayerControllerTest : public PlayerController
//{
//public:
//    PlayerControllerTest(GeneralView* view)
//                          : PlayerController(view) {}
//    virtual ~PlayerControllerTest() {}

//    PlayerModel* getPlayerModel() { return m_player; }
//    void createPlayer()
//    {
//        m_player = new PlayerModel;
//    }
//};

//class PlayerControllerTestsClass : public testing::Test
//{
//public:
//    void SetUp()
//    {
//        g_imageStorage = new ImageStorageStub;
//        g_soundStorage = new SoundStorageStub;
//    }
//    void TearDown()
//    {
//        delete g_imageStorage;
//        delete g_soundStorage;
//    }
//};

//TEST_F(PlayerControllerTestsClass, AbortPlayer_CheckIfPlayerAfterDeleteWillBeSetToNullptr_Equal)
//{
//    GeneralView*         view = new GeneralView;
//    PlayerControllerTest playerController(view);
//    playerController.createPlayer();
//    delete playerController.getPlayerModel(); //Player pointer should have non zero and not valid value

//    playerController.abortPlayer();
//    PlayerModel* resultPlayer = playerController.getPlayerModel();

//    EXPECT_TRUE(resultPlayer == nullptr);
//    delete view;
//}

//TEST_F(PlayerControllerTestsClass, CreateNewPlayer_CheckIfWillCreateNewPlayerWhenOldPlayerWasDefeated_IsEqual)
//{
//    GeneralView*         view = new GeneralView;
//    PlayerControllerTest playerController(view); // default Player is not created
//    QSignalSpy           signalAdd(&playerController, &PlayerControllerTest::addPlayerToScene);
//    signalAdd.wait(utdef::minSignalTimeDelay);

//    playerController.createNewPlayer();
//    PlayerModel*   resultPlayer           = playerController.getPlayerModel();
//    int            resultSignalCount      = signalAdd.count();
//    QGraphicsItem* resultPlayerFromSignal = qvariant_cast<QGraphicsItem*>(signalAdd.takeFirst().at(0));

//    EXPECT_TRUE(resultPlayer != nullptr);
//    EXPECT_EQ(resultSignalCount,      1);
//    EXPECT_EQ(resultPlayerFromSignal, resultPlayer);
//    delete view;
//}

//TEST_F(PlayerControllerTestsClass, CreateNewPlayer_CheckIfWillCreateNewPlayerWhenOldPlayerIsStillAlive_IsEqual)
//{
//    GeneralView*         view = new GeneralView;
//    PlayerControllerTest playerController(view);
//    QSignalSpy           signalAdd(&playerController, &PlayerControllerTest::addPlayerToScene);
//    signalAdd.wait(utdef::minSignalTimeDelay);
//    playerController.createPlayer();
//    PlayerModel*         oldPlayer  = playerController.getPlayerModel();
//    oldPlayer->setHealth(500);

//    playerController.createNewPlayer();
//    PlayerModel*   resultPlayer           = playerController.getPlayerModel();
//    int            resultPlayerHealth     = resultPlayer->getHealth();
//    int            resultSignalCount      = signalAdd.count();
//    QGraphicsItem* resultPlayerFromSignal = qvariant_cast<QGraphicsItem*>(signalAdd.takeFirst().at(0));

//    EXPECT_EQ(resultPlayerHealth,     def::maxPlayerHealth);
//    EXPECT_EQ(resultSignalCount,      1);
//    EXPECT_EQ(resultPlayerFromSignal, resultPlayer);
//    delete view;
//}

//TEST_F(PlayerControllerTestsClass, Defeated_CheckIfWillEmitPlayerDefeatedSingal_IsEqual)
//{
//    GeneralView*         view = new GeneralView;
//    PlayerControllerTest playerController(view);
//    playerController.createPlayer();
//    view->addGameObject(playerController.getPlayerModel());
//    QSignalSpy           signalDefeated(&playerController, &PlayerControllerTest::playerDefeated);
//    signalDefeated.wait(utdef::minSignalTimeDelay);

//    playerController.defeated();
//    int          resultSignalCount = signalDefeated.count();
//    PlayerModel* resultPlayer      = playerController.getPlayerModel();

//    EXPECT_EQ(resultSignalCount, 1);
//    EXPECT_EQ(resultPlayer,      nullptr);
//    delete view;
//}

//TEST_F(PlayerControllerTestsClass, ChangePlayerAtribute_CheckIfWillEmitChangeAtributeSingal_IsEqual)
//{
//    qRegisterMetaType<special_type>();
//    GeneralView*         view = new GeneralView;
//    PlayerControllerTest playerController(view);
//    QSignalSpy           signalDefeated(&playerController, &PlayerControllerTest::changeAtribute);
//    signalDefeated.wait(utdef::minSignalTimeDelay);

//    playerController.changePlayerAtribute(special_type::health);
//    int          resultSignalCount = signalDefeated.count();
//    special_type resultRevardType  = qvariant_cast<special_type>(signalDefeated.takeFirst().at(0));

//    EXPECT_EQ(resultSignalCount, 1);
//    EXPECT_EQ(resultRevardType,  special_type::health);
//    delete view;
//}
