#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/animationplaneview.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/bulletmodel.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QSignalSpy>
#include <tr1/tuple>
#include <QGraphicsScene>

using namespace testing;

Q_DECLARE_METATYPE(coin_type)
Q_DECLARE_METATYPE(special_type)

class PlayerModelTest : public PlayerModel
{
public:
    PlayerModelTest() {}
    virtual ~PlayerModelTest() {}
    bool isOnMovePosition()
    {
        return PlayerModel::isOnMovePosition();
    }
    void checkCollisions()
    {
        PlayerModel::checkCollisions();
    }
    void move()
    {
        PlayerModel::move();
    }
    void animation()
    {
        PlayerModel::animation();
    }

    QPointF       getMovePosition()      const { return m_movePosition; }
    QPointF       getPosition()          const { return QGraphicsItem::pos(); }
    int           getDirection()         const { return m_direction; }
    weapon        getWeapon()            const { return m_weapon; }
    int           getWeaponTier()        const { return m_weaponTier; }
    int           getMoveTimeDelay()     const { return m_moveTimeDelay; }
    int           getFireTimeDelay()     const { return m_weapon.fireTimeDelay; }
    const QTimer& getMoveTimer()         const { return m_moveTimer; }
    const QTimer& getFireTimer()         const { return m_fireTimer; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
    int           getAnimationFrameIdx() const { return  m_animationFrameIdx; }
    void          setMovePosition(QPointF newPosition) { m_movePosition = newPosition; }
    void          setDirection(int newDirection)       { m_direction    = newDirection; }
    void          setWeapon(weapon newWeapon)          { m_weapon       = newWeapon; }
    void          setWeaponTier(int newWeaponTier)     { m_weaponTier   = newWeaponTier; }
    void          startFireTimer()                     { m_fireTimer.start(); }
};

class PlayerModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage       = new ImageStorageStub;
        g_soundStorage       = new SoundStorageStub;
        m_displayWidget      = new QWidget;
        g_animationPlaneView = new AnimationPlaneView(m_displayWidget);
    }
    void TearDown()
    {
        delete g_animationPlaneView;
        delete m_displayWidget;
        delete g_imageStorage;
        delete g_soundStorage;
    }

private:
    QWidget* m_displayWidget;
};

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithEnemyBulletPlayer_ShouldHitButDontBeDefeated)
{
    QPointF          playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel("bullet_enemy",
                                              game_object_type::enemy_bullet,
                                              playerPosition,
                                              50,
                                              5,
                                              50);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    scene->addItem(bullet);
    scene->addItem(player);
    int startNumOfItemsOnScene = scene->items().size();
    signalSubtractHealth.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signallSubtractHealthCount = signalSubtractHealth.count();
    int resultNumOfItemsOnScene    = scene->items().size();

    EXPECT_EQ(2, startNumOfItemsOnScene);
    EXPECT_EQ(1, signallSubtractHealthCount);
    EXPECT_EQ(1, resultNumOfItemsOnScene);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithSelfBulletPlayer_ShouldDoNothing)
{
    QPointF          playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel("bullet_default",
                                              game_object_type::player_bullet,
                                              playerPosition,
                                              50,
                                              5,
                                              50);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    scene->addItem(bullet);
    scene->addItem(player);
    int startNumOfItemsOnScene = scene->items().size();
    signalSubtractHealth.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signallSubtractHealthCount = signalSubtractHealth.count();
    int resultNumOfItemsOnScene    = scene->items().size();

    EXPECT_EQ(2, startNumOfItemsOnScene);
    EXPECT_EQ(0, signallSubtractHealthCount);
    EXPECT_EQ(2, resultNumOfItemsOnScene);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithCoinReward_RewardShouldBeCollected)
{
    qRegisterMetaType<coin_type>();
    QPointF          playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    RewardCoinModel* coin   = new RewardCoinModel(coin_type::bronze);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalAddHealth(player, &PlayerModelTest::addHealthPoints);
    QSignalSpy       signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    QSignalSpy       signalCoin(coin, &RewardCoinModel::collected);
    coin->setPos(playerPosition);
    scene->addItem(coin);
    scene->addItem(player);
    signalCoin.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalAddHealthCount      = signalAddHealth.count();
    int signalSubtractHealthCount = signalSubtractHealth.count();
    int signalCoinCount           = signalCoin.count();

    EXPECT_EQ(0, signalAddHealthCount);
    EXPECT_EQ(0, signalSubtractHealthCount);
    EXPECT_EQ(1, signalCoinCount);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithSpecialReward_RewardShouldBeCollected)
{
    qRegisterMetaType<special_type>();
    QPointF             playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*     scene   = new QGraphicsScene();
    RewardSpecialModel* special = new RewardSpecialModel(special_type::weaponRed);
    PlayerModelTest*    player  = new PlayerModelTest;
    QSignalSpy          signalAddHealth(player, &PlayerModelTest::addHealthPoints);
    QSignalSpy          signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    QSignalSpy          signalSpecial(special, &RewardSpecialModel::collected);
    special->setPos(playerPosition);
    scene->addItem(special);
    scene->addItem(player);
    signalSpecial.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalAddHealthCount      = signalAddHealth.count();
    int signalSubtractHealthCount = signalSubtractHealth.count();
    int signalSpecialCount        = signalSpecial.count();

    EXPECT_EQ(0, signalAddHealthCount);
    EXPECT_EQ(0, signalSubtractHealthCount);
    EXPECT_EQ(1, signalSpecialCount);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithEnemyTier1_PlayerShouldHit)
{
    QPointF              playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*      scene     = new QGraphicsScene();
    NiceMock<RandomGeneratorStub>* generator = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generator, bounded(_,_)).WillByDefault(Return(0));
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest;
    QSignalSpy           signalAddHealth(player, &PlayerModelTest::addHealthPoints);
    QSignalSpy           signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    enemy->setPos(playerPosition);
    scene->addItem(enemy);
    scene->addItem(player);
    int startNumOfItemsOnScene = scene->items().size();
    signalAddHealth.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalAddHealthCount      = signalAddHealth.count();
    int signalSubtractHealthCount = signalSubtractHealth.count();
    int resultNumOfItemsOnScene   = scene->items().size();

    EXPECT_EQ(2, startNumOfItemsOnScene);
    EXPECT_EQ(1, resultNumOfItemsOnScene);
    EXPECT_EQ(0, signalAddHealthCount);
    EXPECT_EQ(1, signalSubtractHealthCount);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithAllCollidingTypes_PlayerShouldHitAndRewardsShouldBeCollected)
{
    qRegisterMetaType<coin_type>();
    qRegisterMetaType<special_type>();
    QPointF              playerPosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*      scene     = new QGraphicsScene();
    BulletModel*         bullet    = new BulletModel("bullet_enemy",
                                                     game_object_type::enemy_bullet,
                                                     playerPosition,
                                                     50,
                                                     5,
                                                     50);
    RewardCoinModel*     coin      = new RewardCoinModel(coin_type::bronze);
    RewardSpecialModel*  special   = new RewardSpecialModel(special_type::weaponRed);
    NiceMock<RandomGeneratorStub>* generator = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generator, bounded(_,_)).WillByDefault(Return(0));
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest;
    QSignalSpy           signalAddHealth(player, &PlayerModelTest::addHealthPoints);
    QSignalSpy           signalSubtractHealth(player, &PlayerModelTest::subtractHealthPoints);
    QSignalSpy           signalCoin(coin, &RewardCoinModel::collected);
    QSignalSpy           signalSpecial(special, &RewardSpecialModel::collected);
    coin->setPos(playerPosition);
    special->setPos(playerPosition);
    enemy->setPos(playerPosition);
    scene->addItem(bullet);
    scene->addItem(coin);
    scene->addItem(special);
    scene->addItem(enemy);
    scene->addItem(player);
    int startNumOfItemsOnScene = scene->items().size();
    signalSpecial.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int resultNumOfItemsOnScene   = scene->items().size();
    int signalAddHealthCount      = signalAddHealth.count();
    int signalSubtractHealthCount = signalSubtractHealth.count();
    int signalCoinCount           = signalCoin.count();
    int signalSpecialCount        = signalSpecial.count();

    EXPECT_EQ(5, startNumOfItemsOnScene);
    EXPECT_EQ(1, resultNumOfItemsOnScene);
    EXPECT_EQ(0, signalAddHealthCount);
    EXPECT_EQ(2, signalSubtractHealthCount);
    EXPECT_EQ(1, signalCoinCount);
    EXPECT_EQ(1, signalSpecialCount);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInCurrentPositionRange_ShouldReturnTrueAndDirectionShouldBe90)
{
    QPointF          movePosition(def::halfSceneWidth, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_TRUE(result);
    EXPECT_EQ(90, resultDirection);
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInDiffrentButInRange_ShouldReturnTrueAndDirectionShouldBe315)
{
    QPointF          movePosition(def::halfSceneWidth - 3, def::halfSceneHeight - 3);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_TRUE(result);
    EXPECT_EQ(315, resultDirection);
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInDiffrentAndOutOfRange_ShouldReturnFalseAndDirectionShouldBe78)
{
    QPointF          movePosition(def::halfSceneWidth + 100, def::halfSceneHeight - 20);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_FALSE(result);
    EXPECT_EQ(78, resultDirection);
    delete scene;
}

TEST_F(PlayerModelTestsClass, Start_CheckIfAllTimersWillBeActive_ShouldActivateMoveAndAnimationTimers)
{
    PlayerModelTest player;

    player.start();
    const QTimer& resultMoveTimer = player.getMoveTimer();
    const QTimer& resultAnimTimer = player.getAnimationTimer();

    EXPECT_TRUE(resultMoveTimer.isActive());
    EXPECT_TRUE(resultAnimTimer.isActive());
}

TEST_F(PlayerModelTestsClass, Stop_CheckIfAllTimersWillBeNotActive_ShouldDeactivateAllTimers)
{
    PlayerModelTest player;

    player.stop();
    const QTimer& resultFireTimer = player.getFireTimer();
    const QTimer& resultMoveTimer = player.getMoveTimer();
    const QTimer& resultAnimTimer = player.getAnimationTimer();

    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FALSE(resultAnimTimer.isActive());
}

TEST_F(PlayerModelTestsClass, Move_IsOnMovePositionIsTrue_PlayerShouldNotMove)
{
    QPointF          movePosition(def::halfSceneWidth, def::halfSceneHeight);
    QPointF          expectedPosition(def::halfSceneWidth  - def::animationFrameWidth  / 2,
                                      def::halfSceneHeight - def::animationFrameWidth  / 2);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    player->move();
    QPointF resultPosition = player->getPosition();

    EXPECT_FLOAT_EQ(expectedPosition.x(), resultPosition.x());
    EXPECT_FLOAT_EQ(expectedPosition.y(), resultPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsOnMovePositionIsFalse_PlayerShouldMoveUpBy5Pixels)
{
    QPointF          movePosition(def::halfSceneWidth, def::halfSceneHeight - 100);
    QPointF          expectedPosition(def::halfSceneWidth  - def::animationFrameWidth  / 2,
                                      def::halfSceneHeight - def::animationFrameHeight / 2 - def::moveVectorLength);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    player->move();
    QPointF resultPosition = player->getPosition();

    EXPECT_FLOAT_EQ(expectedPosition.x(), resultPosition.x());
    EXPECT_FLOAT_EQ(expectedPosition.y(), resultPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, ChangeMovePosition_NewDirectionIsDiffrentThanCurrent_IsEqual)
{
    QPointF         expectedMovePosition(def::halfSceneWidth + 50, def::halfSceneHeight + 50);
    PlayerModelTest playerModel;

    playerModel.changeMovePosition(QPointF(def::halfSceneWidth + 50, def::halfSceneHeight + 50));
    QPointF resultMovePosition = playerModel.getMovePosition();

    EXPECT_FLOAT_EQ(expectedMovePosition.x(), resultMovePosition.x());
    EXPECT_FLOAT_EQ(expectedMovePosition.y(), resultMovePosition.y());
}

TEST_F(PlayerModelTestsClass, StartFire_CheckCorrectWorkingWithDefaultConfiguration_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.startFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_TRUE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::defaultPlayerFireTimeDelay, resultFireTimer.interval());
}

TEST_F(PlayerModelTestsClass, StopFire_CheckCorrectWorking_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.startFireTimer();

    playerModel.stopFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(defaultWeapon.fireTimeDelay, resultFireTimer.interval());
}

TEST_F(PlayerModelTestsClass, ChangeAtribute_CollectedHealthReward_ShouldSendAddHealthPoints)
{
    PlayerModelTest player;
    QSignalSpy      signalAddHealth(&player, &PlayerModelTest::addHealthPoints);
    signalAddHealth.wait(utdef::minSignalTimeDelay);

    player.changeAtribute(special_type::health);
    int  resutlSignalAddHealthCount = signalAddHealth.count();
    auto resutlSignalAddHealth      = signalAddHealth.takeFirst();

    EXPECT_EQ(1, resutlSignalAddHealthCount);
    EXPECT_EQ(def::healthRewardValue, resutlSignalAddHealth.at(0).toInt());
}

TEST_F(PlayerModelTestsClass, Animation_RunOneTime_ShouldIncreaseAnimationFrameIdxBy1)
{
    PlayerModelTest playerModel;

    playerModel.animation();
    int resultAnimationFrameIdx = playerModel.getAnimationFrameIdx();

    EXPECT_EQ(1, resultAnimationFrameIdx);
}

TEST_F(PlayerModelTestsClass, Animation_RunManyTimes_ShouldResetIdxTo0)
{
    PlayerModelTest playerModel;

    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    int resultAnimationFrameIdx = playerModel.getAnimationFrameIdx();
    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    playerModel.animation();
    int resultAnimationFrameIdxReset = playerModel.getAnimationFrameIdx();

    EXPECT_EQ(3, resultAnimationFrameIdx);
    EXPECT_EQ(0, resultAnimationFrameIdxReset);
}

typedef std::tr1::tuple<weapon, int, special_type, weapon> input_params;

class PlayerModelTestsParamClass : public testing::TestWithParam<input_params>
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

TEST_P(PlayerModelTestsParamClass, ChangeAtribute_CollectedWeapon_IsEqual)
{
    weapon          currentWeapon         = std::tr1::get<0>(GetParam());
    int             currentWeaponTier     = std::tr1::get<1>(GetParam());
    special_type    newWeaponRewardType   = std::tr1::get<2>(GetParam());
    weapon_type     expectedWeaponType    = std::tr1::get<3>(GetParam()).type;
    int             expectedFireTimeDelay = std::tr1::get<3>(GetParam()).fireTimeDelay;
    QGraphicsScene scene;
    PlayerModelTest* player = new PlayerModelTest;
    player->setWeapon(currentWeapon);
    player->setWeaponTier(currentWeaponTier);
    scene.addItem(player);

    player->changeAtribute(newWeaponRewardType);
    weapon        resultWeapon    = player->getWeapon();
    const QTimer& resultFireTimer = player->getFireTimer();

    EXPECT_EQ(expectedWeaponType, resultWeapon.type);
    EXPECT_FLOAT_EQ(expectedFireTimeDelay, resultFireTimer.interval());
}

INSTANTIATE_TEST_SUITE_P(ChangeAtribute,
                         PlayerModelTestsParamClass,
                         testing::Values(std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponRed,    weapons[0]),
                                         std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponYellow, weapons[5]),
                                         std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponBlue,   weapons[10]),
                                         std::tr1::make_tuple(weapons[8],    3, special_type::weaponRed,    weapons[0]),
                                         std::tr1::make_tuple(weapons[0],    0, special_type::weaponRed,    weapons[1]),
                                         std::tr1::make_tuple(weapons[4],    4, special_type::weaponRed,    weapons[4]),
                                         std::tr1::make_tuple(weapons[4],    4, special_type::weaponBlue,   weapons[10])
                                         ));
