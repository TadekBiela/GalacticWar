#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include <QSignalSpy>
#include <tr1/tuple>

class PlayerModelTest : public PlayerModel
{
public:
    explicit PlayerModelTest() {}

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
    void          setHealth(int healthValue)       { m_health = healthValue; }
    void          setWeapon(weapon newWeapon)      { m_weapon     = newWeapon; }
    void          setWeaponTier(int newWeaponTier) { m_weaponTier = newWeaponTier; }
    void          startFireTimer()                 { m_fireTimer.start(); }
};

class PlayerModelTestsClass : public testing::Test
{
};

TEST_F(PlayerModelTestsClass, PlayerModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    QPointF expectedPosition(QPointF(def::halfSceneWight, def::halfSceneHeight));

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

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsFalsePlayerShouldntMove_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight);
    PlayerModelTest playerModel;
    playerModel.setIsMovingFlag(false);

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, Move_IsMovingFlagIsTruePlayerShouldMoveUpBy10Pixels_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight - 10);
    PlayerModelTest playerModel;
    playerModel.setIsMovingFlag(true);

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
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

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthShouldIncrease_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setHealth(500);
    QSignalSpy signalChange(&playerModel, &PlayerModelTest::playerChangeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changePlayerAtribute(special_type::health);
    int             resultHealth            = playerModel.getHealth();
    int             resultSignalChangeCount = signalChange.count();
//    QList<QVariant> resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     600);
    EXPECT_EQ(resultSignalChangeCount,          1);
//    EXPECT_EQ(resultSignalChange.at(0).toInt(), 60);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthIsMax_IsEqual)
{
    PlayerModelTest playerModel; //Max health is default
    QSignalSpy      signalChange(&playerModel, &PlayerModelTest::playerChangeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changePlayerAtribute(special_type::health);
    int             resultHealth            = playerModel.getHealth();
    int             resultSignalChangeCount = signalChange.count();
    QList<QVariant> resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     1000);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 100);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedHealthRewardChangeHealthSignalShouldBeSendAndPlayerHealthIsNearMaxAndShouldBeMax_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setHealth(990);
    QSignalSpy      signalChange(&playerModel, &PlayerModelTest::playerChangeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changePlayerAtribute(special_type::health);
    int             resultHealth            = playerModel.getHealth();
    int             resultSignalChangeCount = signalChange.count();
    QList<QVariant> resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultHealth,                     1000);
    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 100);
}

typedef std::tr1::tuple<weapon, int, special_type, weapon> input_params;

class PlayerModelTestsParamClass : public testing::TestWithParam<input_params>
{
};

TEST_P(PlayerModelTestsParamClass, ChangePlayerAtribute_CollectedWeapon_IsEqual)
{
    weapon       currentWeapon         = std::tr1::get<0>(GetParam());
    int          currentWeaponTier     = std::tr1::get<1>(GetParam());
    special_type newWeaponRewardType   = std::tr1::get<2>(GetParam());
    weapon_type  expectedWeaponType    = std::tr1::get<3>(GetParam()).type;
    int          expectedFireTimeDelay = std::tr1::get<3>(GetParam()).fireTimeDelay;
    PlayerModelTest playerModel;
    playerModel.setWeapon(currentWeapon);
    playerModel.setWeaponTier(currentWeaponTier);

    playerModel.changePlayerAtribute(newWeaponRewardType);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                 expectedWeaponType);
    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  expectedFireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), expectedFireTimeDelay, 1);
}

INSTANTIATE_TEST_CASE_P(ChangePlayerAtribute,
                        PlayerModelTestsParamClass,
                        testing::Values(std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponRed,    weapons[0]),
                                        std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponYellow, weapons[5]),
                                        std::tr1::make_tuple(defaultWeapon, 0, special_type::weaponBlue,   weapons[10]),
                                        std::tr1::make_tuple(weapons[8],    3, special_type::weaponRed,    weapons[0]),
                                        std::tr1::make_tuple(weapons[0],    0, special_type::weaponRed,    weapons[1]),
                                        std::tr1::make_tuple(weapons[4],    4, special_type::weaponRed,    weapons[4]),
                                        std::tr1::make_tuple(weapons[4],    4, special_type::weaponBlue,   weapons[10])
                                        ));


