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

    QPointF       getPosition()      const { return QGraphicsItem::pos(); }
    bool          getIsMovingFlag()  const { return m_isMoving; }
    int           getDirection()     const { return m_direction; }
    int           getHealth()        const { return m_health; }
    weapon        getWeapon()        const { return m_weapon; }
    int           getWeaponTier()    const { return m_weaponTier; }
    int           getMoveTimeDelay() const { return m_moveTimeDelay; }
    int           getFireTimeDelay() const { return m_weapon.fireTimeDelay; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
    void          setIsMovingFlag(bool isMoving)   { m_isMoving   = isMoving; }
    void          setDirection(int newDirection)   { m_direction  = newDirection; }
    void          setHealth(int healthValue)       { m_health     = healthValue; }
    void          setWeapon(weapon newWeapon)      { m_weapon     = newWeapon; }
    void          setWeaponTier(int newWeaponTier) { m_weaponTier = newWeaponTier; }
    void          startFireTimer()                 { m_fireTimer.start(); }
};

class PlayerModelTestsClass : public testing::Test
{
};

TEST_F(PlayerModelTestsClass, PlayerModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    QPointF expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 30);

    PlayerModelTest playerModel;
    int           resultIsMovingFlag      = playerModel.getIsMovingFlag();
    int           resultDirection         = playerModel.getDirection();
    QPointF       resultPosition          = playerModel.getPosition();
    int           resultHealth            = playerModel.getHealth();
    weapon        resultWeapon            = playerModel.getWeapon();
    int           resultWeaponTier        = playerModel.getWeaponTier();
    int           resultFireMoveDelay     = playerModel.getMoveTimeDelay();
    int           resultFireTimeDelay     = playerModel.getFireTimeDelay();
    const QTimer& resultMoveTimer         = playerModel.getMoveTimer();
    const QTimer& resultFireTimer         = playerModel.getFireTimer();

    EXPECT_EQ(      resultIsMovingFlag,              false);
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
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsFalseAndThereIsNoCollisionsPlayerShouldntMove_IsEqual)
{
    QPointF          expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 30);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(player);
    player->setIsMovingFlag(false);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    QPointF resultPosition    = player->getPosition();
    int     signalHealthCount = signalHealth.count();
    int     signalDefeatCount = signalDefeat.count();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    EXPECT_EQ(signalHealthCount, 0);
    EXPECT_EQ(signalDefeatCount, 0);
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndThereIsNoCollisionsPlayerShouldMoveUpBy10Pixels_IsEqual)
{
    QPointF          expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*  scene  = new QGraphicsScene();
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(player);
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    QPointF resultPosition = player->getPosition();
    int     signalHealthCount = signalHealth.count();
    int     signalDefeatCount = signalDefeat.count();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    EXPECT_EQ(signalHealthCount, 0);
    EXPECT_EQ(signalDefeatCount, 0);
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithBulletPlayerShouldMoveAndHitButDontBeDefeated_IsEqual)
{
    QPointF          expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel(bullet_type::enemyBullet, expectedPosition, 50, 5, 50);
    PlayerModelTest* player = new PlayerModelTest; //default health is 1000
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(bullet);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  950);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       950);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithSelfBulletPlayerShouldOnlyMove_IsEqual)
{
    QPointF          expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*  scene  = new QGraphicsScene();
    BulletModel*     bullet = new BulletModel(bullet_type::playerDefaultBullet, expectedPosition, 50, 5, 50);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    scene->addItem(bullet);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(resultItemsOnScene, 2);
    EXPECT_EQ(resultHealth,       1000);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithCoinRewardPlayerShouldMoveAndRewardShouldBeCollected_IsEqual)
{
    qRegisterMetaType<coin_type>();
    QPointF          expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*  scene  = new QGraphicsScene();
    RewardCoinModel* coin   = new RewardCoinModel(coin_type::bronze);
    PlayerModelTest* player = new PlayerModelTest;
    QSignalSpy       signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy       signalDefeat(player, &PlayerModelTest::defeated);
    QSignalSpy       signalCoin(coin, &RewardCoinModel::collected);
    coin->setPos(expectedPosition);
    scene->addItem(coin);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalCoinCount    = signalCoin.count();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalCoinCount,    1);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       1000);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithSpecialRewardPlayerShouldMoveAndRewardShouldBeCollected_IsEqual)
{
    qRegisterMetaType<special_type>();
    QPointF             expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*     scene   = new QGraphicsScene();
    RewardSpecialModel* special = new RewardSpecialModel(special_type::weaponRed);
    PlayerModelTest*    player  = new PlayerModelTest;
    QSignalSpy          signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy          signalDefeat(player, &PlayerModelTest::defeated);
    QSignalSpy          signalSpecial(special, &RewardSpecialModel::collected);
    special->setPos(expectedPosition);
    scene->addItem(special);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalSpecialCount = signalSpecial.count();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  0);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalSpecialCount, 1);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       1000);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithEnemyTier1PlayerShouldMoveAndHitButDontBeDefeated_IsEqual)
{
    QPointF              expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*      scene     = new QGraphicsScene();
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest; //default health is 1000
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
    enemy->setPos(expectedPosition);
    scene->addItem(enemy);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  900);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       900);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithEnemyTier1PlayerShouldBeDefeated_IsEqual)
{
    QPointF              expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*      scene     = new QGraphicsScene();
    RandomGeneratorStub* generator = new RandomGeneratorStub;
    EnemyModel*          enemy     = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player    = new PlayerModelTest;
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
    enemy->setPos(expectedPosition);
    scene->addItem(enemy);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    player->setHealth(90);
    signalDefeat.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int     resultItemsOnScene = scene->items().size();

    EXPECT_EQ(startItemsOnScene,  2);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  1);
    EXPECT_EQ(signalHealthValue,  0);
    EXPECT_EQ(resultItemsOnScene, 0);
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTrueAndPlayerCollidingWithAllCollidingTypesPlayerShouldMoveAndHitButDontBeDefeated_IsEqual)
{
    qRegisterMetaType<coin_type>();
    qRegisterMetaType<special_type>();
    QPointF              expectedPosition(def::halfSceneWight - 30, def::halfSceneHeight - 40);
    QGraphicsScene*      scene       = new QGraphicsScene();
    BulletModel*         bullet      = new BulletModel(bullet_type::enemyBullet, expectedPosition, 50, 5, 50);
    RewardCoinModel*     coin        = new RewardCoinModel(coin_type::bronze);
    RewardSpecialModel*  special     = new RewardSpecialModel(special_type::weaponRed);
    RandomGeneratorStub* generator   = new RandomGeneratorStub;
    EnemyModel*          enemy       = new EnemyModelType1(QPointF(0,0), generator);
    PlayerModelTest*     player      = new PlayerModelTest; //default health is 1000
    QSignalSpy           signalHealth(player, &PlayerModelTest::changeHealth);
    QSignalSpy           signalDefeat(player, &PlayerModelTest::defeated);
    QSignalSpy           signalCoin(coin, &RewardCoinModel::collected);
    QSignalSpy           signalSpecial(special, &RewardSpecialModel::collected);
    coin->setPos(expectedPosition);
    special->setPos(expectedPosition);
    enemy->setPos(expectedPosition);
    scene->addItem(bullet);
    scene->addItem(coin);
    scene->addItem(special);
    scene->addItem(enemy);
    scene->addItem(player);
    int startItemsOnScene = scene->items().size();
    player->setIsMovingFlag(true);
    signalSpecial.wait(utdef::minSignalTimeDelay);

    player->move();
    int     signalHealthCount  = signalHealth.count();
    int     signalDefeatCount  = signalDefeat.count();
    int     signalCoinCount    = signalCoin.count();
    int     signalSpecialCount = signalSpecial.count();
    int     signalHealthValue  = signalHealth.takeFirst().at(0).toInt();
    int     resultItemsOnScene = scene->items().size();
    int     resultHealth       = player->getHealth();
    QPointF resultPosition     = player->getPosition();

    EXPECT_EQ(startItemsOnScene,  5);
    EXPECT_EQ(signalHealthCount,  1);
    EXPECT_EQ(signalDefeatCount,  0);
    EXPECT_EQ(signalHealthValue,  850);
    EXPECT_EQ(resultItemsOnScene, 1);
    EXPECT_EQ(resultHealth,       850);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
    delete generator;
    delete scene;
}

TEST_F(PlayerModelTestsClass, ChangeDirection_NewDirectionIsEqualAsCurrentPlayerPositionShouldntMove_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.changeDirection(QPointF(def::halfSceneWight, def::halfSceneHeight));
    bool resultIsMovingFlag = playerModel.getIsMovingFlag();
    int  resultDirection    = playerModel.getDirection();

    EXPECT_EQ(resultIsMovingFlag, false);
    EXPECT_EQ(resultDirection,    90);
}

TEST_F(PlayerModelTestsClass, ChangeDirection_NewDirectionIsOnly5PixLeftSideOfCurrentPlayerPositionShouldMoveOnly5pix_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.changeDirection(QPointF(def::halfSceneWight - 5, def::halfSceneHeight));
    bool resultIsMovingFlag = playerModel.getIsMovingFlag();
    int  resultDirection    = playerModel.getDirection();

    EXPECT_EQ(resultIsMovingFlag, false);
    EXPECT_EQ(resultDirection,    270);
}

TEST_F(PlayerModelTestsClass, ChangeDirection_NewDirectionIsEqualAsDefMoveVectorLenghtUpOfCurrentPlayerPositionShouldMoveUp_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.changeDirection(QPointF(def::halfSceneWight, def::halfSceneHeight - def::moveVectorLength));
    bool resultIsMovingFlag = playerModel.getIsMovingFlag();
    int  resultDirection    = playerModel.getDirection();

    EXPECT_EQ(resultIsMovingFlag, true);
    EXPECT_EQ(resultDirection,    0);
}

TEST_F(PlayerModelTestsClass, ChangeDirection_NewDirectionIsRightDownOfCurrentPlayerPositionShouldMoveBy10Pixels135Deg_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.changeDirection(QPointF(def::halfSceneWight + 50, def::halfSceneHeight + 50));
    bool resultIsMovingFlag = playerModel.getIsMovingFlag();
    int  resultDirection    = playerModel.getDirection();

    EXPECT_EQ(resultIsMovingFlag, true);
    EXPECT_EQ(resultDirection,    135);
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
    weapon       currentWeapon         = std::tr1::get<0>(GetParam());
    int          currentWeaponTier     = std::tr1::get<1>(GetParam());
    special_type newWeaponRewardType   = std::tr1::get<2>(GetParam());
    weapon_type  expectedWeaponType    = std::tr1::get<3>(GetParam()).type;
    int          expectedFireTimeDelay = std::tr1::get<3>(GetParam()).fireTimeDelay;
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


