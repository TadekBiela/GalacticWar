#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/playercontroller.hpp"
#include "../app/playermodel.hpp"
#include "../app/rewardtypes.hpp"
#include <QSignalSpy>

Q_DECLARE_METATYPE(GameObject*)
Q_DECLARE_METATYPE(special_type)

class PlayerControllerTest : public PlayerController
{
public:
    PlayerControllerTest(ControlPlane* controller,
                         GameplayView* view)
        : PlayerController(controller,
                           view) {}
    virtual ~PlayerControllerTest() {}

    PlayerModel* getPlayerModel() { return m_model; }
};

class PlayerControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(PlayerControllerTestsClass, Create_CheckCorrectWorking_ShouldCreateNewPlayerModelAndSendSignalAddPlayerToScene)
{
    QWidget              displayWidget;
    ControlPlane         controller(&displayWidget);
    GameplayView         view(&displayWidget);
    PlayerControllerTest playerController(&controller, &view);
    QSignalSpy           signalAdd(&playerController, &PlayerControllerTest::addPlayerToScene);
    signalAdd.wait(utdef::minSignalTimeDelay);

    playerController.create();
    PlayerModel* resultPlayer           = playerController.getPlayerModel();
    int          resultSignalCount      = signalAdd.count();
    GameObject*  resultPlayerFromSignal = qvariant_cast<GameObject*>(signalAdd.takeFirst().at(0));

    EXPECT_TRUE(nullptr != resultPlayer);
    EXPECT_EQ(1,            resultSignalCount);
    EXPECT_EQ(resultPlayer, resultPlayerFromSignal);
}

TEST_F(PlayerControllerTestsClass, Destroy_CheckCorrectWorking_ShouldDestroyPlayerModelAndSetPtrToNullptr)
{
    QWidget              displayWidget;
    ControlPlane         controller(&displayWidget);
    GameplayView         view(&displayWidget);
    PlayerControllerTest playerController(&controller, &view);
    playerController.create();

    playerController.destroy();
    PlayerModel* resultPlayer = playerController.getPlayerModel();

    EXPECT_TRUE(nullptr == resultPlayer);
}
