#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/bulletmodel.hpp"
#include "../app/rewardcoinmodel.hpp"
#include "../app/rewardspecialmodel.hpp"
#include <QSignalSpy>
#include <tr1/tuple>
#include <QGraphicsScene>

Q_DECLARE_METATYPE(coin_type)
Q_DECLARE_METATYPE(special_type)

class PlayerModelTest : public PlayerModel
{
public:
    PlayerModelTest() {}
    virtual ~PlayerModelTest() {}

    QPointF       getMovePosition()  const { return m_movePosition; }
    QPointF       getPosition()      const { return QGraphicsItem::pos(); }
    int           getDirection()     const { return m_direction; }
    int           getHealth()        const { return m_health; }
    weapon        getWeapon()        const { return m_weapon; }
    int           getWeaponTier()    const { return m_weaponTier; }
    int           getMoveTimeDelay() const { return m_moveTimeDelay; }
    int           getFireTimeDelay() const { return m_weapon.fireTimeDelay; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
    void          setMovePosition(QPointF newPosition) { m_movePosition = newPosition; }
    void          setDirection(int newDirection)       { m_direction  = newDirection; }
    void          setHealth(int healthValue)           { m_health     = healthValue; }
    void          setWeapon(weapon newWeapon)          { m_weapon     = newWeapon; }
    void          setWeaponTier(int newWeaponTier)     { m_weaponTier = newWeaponTier; }
    void          startFireTimer()                     { m_fireTimer.start(); }
};

class PlayerModelTestsClass : public testing::Test
{
};

TEST_F(PlayerModelTestsClass, PlayerModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    QPointF expectedPosition(def::halfSceneWight  - def::animationFrameWight  / 2,
                             def::halfSceneHeight - def::animationFrameHeight / 2);

    PlayerModelTest playerModel;
    QPointF       resultMovePosition  = playerModel.getMovePosition();
    int           resultDirection     = playerModel.getDirection();
    QPointF       resultPosition      = playerModel.getPosition();
    int           resultHealth        = playerModel.getHealth();
    weapon        resultWeapon        = playerModel.getWeapon();
    int           resultWeaponTier    = playerModel.getWeaponTier();
    int           resultFireMoveDelay = playerModel.getMoveTimeDelay();
    int           resultFireTimeDelay = playerModel.getFireTimeDelay();
    const QTimer& resultMoveTimer     = playerModel.getMoveTimer();
    const QTimer& resultFireTimer     = playerModel.getFireTimer();

    EXPECT_EQ(      resultDirection,                 0);
    EXPECT_EQ(      resultHealth,                    def::maxPlayerHealth);
    EXPECT_EQ(      resultWeapon.type,               defaultWeapon.type);
    EXPECT_EQ(      resultWeaponTier,                0);
    EXPECT_EQ(      resultFireMoveDelay,             def::defaultPlayerMoveTimeDelay);
    EXPECT_EQ(      resultFireTimeDelay,             defaultWeapon.fireTimeDelay);
    EXPECT_EQ(      resultMoveTimer.isActive(),      false);
    EXPECT_EQ(      resultFireTimer.isActive(),      false);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(),      def::defaultPlayerMoveTimeDelay);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),      defaultWeapon.fireTimeDelay);
    EXPECT_FLOAT_EQ(resultMoveTimer.remainingTime(), -1);
    EXPECT_FLOAT_EQ(resultFireTimer.remainingTime(), -1);
    EXPECT_FLOAT_EQ(resultPosition.x(),              expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(),              expectedPosition.y());
    EXPECT_FLOAT_EQ(resultMovePosition.x(),          def::halfSceneWight);
    EXPECT_FLOAT_EQ(resultMovePosition.y(),          def::halfSceneHeight);
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithBulletPlayerShouldHitButDontBeDefeated_IsEqual)
{
    QPointF          playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel(bullet_type::enemyBullet, playerPosition, 50, 5, 50);
    PlayerModelTest* player = new PlayerModelTest; //default health is 1000
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(bullet);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  95);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       950);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithSelfBulletPlayerShouldDoNothing_IsEqual)
{
    QPointF          playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel(bullet_type::playerDefaultBullet, playerPosition, 50, 5, 50);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(bullet);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(resultItemsOnScene, 2);
    EXPECT_EQ(resultHealth,       1000);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithCoinRewardAndRewardShouldBeCollected_IsEqual)
{
    qRegisterMetaType<coin_type>();
    QPointF          playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    RewardCoinModel* coin   = new RewardCoinModel(coin_type::bronze);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    QSignalSpy       signalCoin(coin, &RewardCoinModel::collected);
    coin->setPos(playerPosition);
    scene->addItem(coin);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalCoinCount    = signalCoin.count();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalCoinCount,    1);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       1000);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithSpecialRewardAndRewardShouldBeCollected_IsEqual)
{
    qRegisterMetaType<special_type>();
    QPointF             playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*     scene   = new QGraphicsScene();
    RewardSpecialModel* special = new RewardSpecialModel(special_type::weaponRed);
    PlayerModelTest*    player  = new PlayerModelTest;
    QSignalSpy          signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy          signalDefeat(player, &PlayerModelTest::defeated);
    QSignalSpy          signalSpecial(special, &RewardSpecialModel::collected);
    special->setPos(playerPosition);
    scene->addItem(special);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalSpecialCount = signalSpecial.count();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalSpecialCount, 1);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       1000);
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithEnemyTier1PlayerShouldHitButDontBeDefeated_IsEqual)
{
    QPointF              playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*      scene     = new QGraphicsScene();
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest; //default health is 1000
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
    enemy->setPos(playerPosition);
    scene->addItem(enemy);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  90);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       900);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithEnemyTier1PlayerShouldBeDefeated_IsEqual)
{
    QPointF              playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*      scene     = new QGraphicsScene();
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest;
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
    enemy->setPos(playerPosition);
    scene->addItem(enemy);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setHealth(90);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int resultItemsOnScene = scene->items().size();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  1);
    EXPECT_EQ(signalHealthValue,  0);
    EXPECT_EQ(resultItemsOnScene, 0);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, CheckCollisions_PlayerCollidingWithAllCollidingTypesPlayerShouldHitButDontBeDefeated_IsEqual)
{
    qRegisterMetaType<coin_type>();
    qRegisterMetaType<special_type>();
    QPointF              playerPosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*      scene     = new QGraphicsScene();
    BulletModel*         bullet    = new BulletModel(bullet_type::enemyBullet, playerPosition, 50, 5, 50);
    RewardCoinModel*     coin      = new RewardCoinModel(coin_type::bronze);
    RewardSpecialModel*  special   = new RewardSpecialModel(special_type::weaponRed);
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest; //default health is 1000
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
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
    int startItemsOnScene = scene->items().size();
    signalSpecial.wait(utdef::minSignalTimeDelay);

    player->checkCollisions();
    int signalHealthCount  = signalHealth.count();
    int signalDefeatCount  = signalDefeat.count();
    int signalCoinCount    = signalCoin.count();
    int signalSpecialCount = signalSpecial.count();
    int signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int resultItemsOnScene = scene->items().size();
    int resultHealth       = player->getHealth();

    EXPECT_EQ(startItemsOnScene,  5);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  85);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       850);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInCurrentPositionRangeAndDirectionShouldBe90_IsEqual)
{
    QPointF          movePosition(def::halfSceneWight, def::halfSceneHeight);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_TRUE(result);
    EXPECT_EQ(resultDirection, 90);
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInDiffrentButInRangeAndDirectionShouldBe315_IsEqual)
{
    QPointF          movePosition(def::halfSceneWight - 3, def::halfSceneHeight - 3);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_TRUE(result);
    EXPECT_EQ(resultDirection, 315);
    delete scene;
}

TEST_F(PlayerModelTestsClass, IsOnMovePosition_NewPositionIsInDiffrentAndOutOfRangeAndDirectionShouldBe78_IsEqual)
{
    QPointF          movePosition(def::halfSceneWight + 100, def::halfSceneHeight - 20);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    bool result = player->isOnMovePosition();
    int resultDirection = player->getDirection();

    EXPECT_FALSE(result);
    EXPECT_EQ(resultDirection, 78);
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsOnMovePositionIsTruePlayerShouldntMove_IsEqual)
{
    QPointF          movePosition(def::halfSceneWight, def::halfSceneHeight);
    QPointF          expectedPosition(def::halfSceneWight  - def::animationFrameWight  / 2,
                                      def::halfSceneHeight - def::animationFrameWight  / 2);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    player->move();
    QPointF resultPosition = player->getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsOnMovePositionIsFalsePlayerShouldMoveUpBy10Pixels_IsEqual)
{
    QPointF          movePosition(def::halfSceneWight, def::halfSceneHeight - 100);
    QPointF          expectedPosition(def::halfSceneWight  - def::animationFrameWight  / 2,
                                      def::halfSceneHeight - def::animationFrameHeight / 2 - 10);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    scene->addItem(player);
    player->setMovePosition(movePosition);

    player->move();
    QPointF resultPosition = player->getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, ChangeMovePosition_NewDirectionIsDiffrentThanCurrent_IsEqual)
{
    QPointF         expectedMovePosition(def::halfSceneWight + 50, def::halfSceneHeight + 50);
    PlayerModelTest playerModel;

    playerModel.changeMovePosition(QPointF(def::halfSceneWight + 50, def::halfSceneHeight + 50));
    QPointF resultMovePosition = playerModel.getMovePosition();

    EXPECT_FLOAT_EQ(resultMovePosition.x(), expectedMovePosition.x());
    EXPECT_FLOAT_EQ(resultMovePosition.y(), expectedMovePosition.y());
}

TEST_F(PlayerModelTestsClass, StartFire_CheckCorrectWorkingWithDefaultConfiguration_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.startFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  defaultWeapon.fireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), defaultWeapon.fireTimeDelay, 1);
}

TEST_F(PlayerModelTestsClass, StopFire_CheckCorrectWorking_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.startFireTimer();

    playerModel.stopFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultFireTimer.isActive(),            false);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),      defaultWeapon.fireTimeDelay);
    EXPECT_FLOAT_EQ(resultFireTimer.remainingTime(), -1);
}

TEST_F(PlayerModelTestsClass, ChangeAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthShouldIncrease_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setHealth(500);
    QSignalSpy signalChange(&playerModel, &PlayerModelTest::changeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changeAtribute(special_type::health);
    int  resultHealth            = playerModel.getHealth();
    int  resultSignalChangeCount = signalChange.count();
    auto resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     600);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 60);
}

TEST_F(PlayerModelTestsClass, ChangeAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthIsMax_IsEqual)
{
    PlayerModelTest playerModel; //Max health is default
    QSignalSpy      signalChange(&playerModel, &PlayerModelTest::changeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changeAtribute(special_type::health);
    int  resultHealth            = playerModel.getHealth();
    int  resultSignalChangeCount = signalChange.count();
    auto resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     1000);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 100);
}

TEST_F(PlayerModelTestsClass, ChangeAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthIsNearMaxAndShouldBeMax_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setHealth(990);
    QSignalSpy      signalChange(&playerModel, &PlayerModelTest::changeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changeAtribute(special_type::health);
    int  resultHealth            = playerModel.getHealth();
    int  resultSignalChangeCount = signalChange.count();
    auto resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     1000);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 100);
}

typedef std::tr1::tuple<weapon, int, special_type, weapon> input_params;

class PlayerModelTestsParamClass : public testing::TestWithParam<input_params>
{
};

TEST_P(PlayerModelTestsParamClass, ChangeAtribute_CollectedWeapon_IsEqual)
{
    weapon          currentWeapon         = std::tr1::get<0>(GetParam());
    int             currentWeaponTier     = std::tr1::get<1>(GetParam());
    special_type    newWeaponRewardType   = std::tr1::get<2>(GetParam());
    weapon_type     expectedWeaponType    = std::tr1::get<3>(GetParam()).type;
    int             expectedFireTimeDelay = std::tr1::get<3>(GetParam()).fireTimeDelay;
    PlayerModelTest playerModel;
    playerModel.setWeapon(currentWeapon);
    playerModel.setWeaponTier(currentWeaponTier);

    playerModel.changeAtribute(newWeaponRewardType);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                expectedWeaponType);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(), expectedFireTimeDelay);
}

INSTANTIATE_TEST_CASE_P(ChangeAtribute,
                        PlayerModelTestsParamClass,
                        testing::Values(std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponRed,    weapons[0]),
                                        std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponYellow, weapons[5]),
                                        std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponBlue,   weapons[10]),
                                        std::tr1::make_tuple(weapons[8],    3, special_type::weaponRed,    weapons[0]),
                                        std::tr1::make_tuple(weapons[0],    0, special_type::weaponRed,    weapons[1]),
                                        std::tr1::make_tuple(weapons[4],    4, special_type::weaponRed,    weapons[4]),
                                        std::tr1::make_tuple(weapons[4],    4, special_type::weaponBlue,   weapons[10])
                                        ));


