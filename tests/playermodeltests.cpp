#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"
#include <QSignalSpy>

class PlayerModelTest : public PlayerModel
{
public:
    explicit PlayerModelTest() {}

    QPointF       getPosition()      const { return QGraphicsItem::pos(); }
    bool          getIsMovingFlag()  const { return m_isMoving; }
    int           getDirection()     const { return m_direction; }
    weapon        getWeapon()        const { return m_weapon; }
    int           getMoveTimeDelay() const { return m_moveTimeDelay; }
    int           getFireTimeDelay() const { return m_weapon.fireTimeDelay; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
    void          setIsMovingFlag(bool isMoving) { m_isMoving  = isMoving; }
    void          setDirection(int newDirection) { m_direction = newDirection; }
    void          setWeapon(weapon newWeapon)    { m_weapon    = newWeapon; }
    void          startFireTimer()               { m_fireTimer.start(); }
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
    weapon        resultWeapon            = playerModel.getWeapon();
    int           resultFireMoveDelay     = playerModel.getMoveTimeDelay();
    int           resultFireTimeDelay     = playerModel.getFireTimeDelay();
    const QTimer& resultMoveTimer         = playerModel.getMoveTimer();
    int           resultMoveRemainingTime = resultMoveTimer.remainingTime();
    const QTimer& resultFireTimer         = playerModel.getFireTimer();

    EXPECT_EQ(      resultIsMovingFlag,              false);
    EXPECT_EQ(      resultDirection,                 0);
    EXPECT_EQ(      resultWeapon.type,               defaultWeapon.type);
    EXPECT_EQ(      resultFireMoveDelay,             def::defaultPlayerMoveTimeDelay);
    EXPECT_EQ(      resultFireTimeDelay,             defaultWeapon.fireTimeDelay);
    EXPECT_EQ(      resultMoveTimer.isActive(),      true);
    EXPECT_EQ(      resultFireTimer.isActive(),      false);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(),      def::defaultPlayerMoveTimeDelay);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),      defaultWeapon.fireTimeDelay);
    EXPECT_NEAR(    resultMoveRemainingTime,         def::defaultPlayerMoveTimeDelay, 1);
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

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedHealthRewardCheckIfChangeHealthSignalWillBeSend_IsEqual)
{
    PlayerModelTest playerModel;
    QSignalSpy      signalChange(&playerModel, &PlayerModelTest::playerChangeHealth);
    signalChange.wait(utdef::minSignalTimeDelay);

    playerModel.changePlayerAtribute(special_reward_type::health);
    int             resultSignalChangeCount = signalChange.count();
    QList<QVariant> resultSignalChange      = signalChange.takeFirst();

    EXPECT_EQ(resultSignalChangeCount,          1);
    EXPECT_EQ(resultSignalChange.at(0).toInt(), 100);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedWeaponRedWhenPlayerHasDefaultWeaponPlayerShouldChangeWeaponToRed_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setWeapon(defaultWeapon);

    playerModel.changePlayerAtribute(special_reward_type::weaponRed);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                 redWeapons[0].type);
    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  redWeapons[0].fireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), redWeapons[0].fireTimeDelay, 1);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedWeaponRedWhenPlayerHasDiffrentWeaponTypePlayerShouldChangeWeaponToRed_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setWeapon(yellowWeapons[3]);

    playerModel.changePlayerAtribute(special_reward_type::weaponRed);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                 redWeapons[0].type);
    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  redWeapons[0].fireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), redWeapons[0].fireTimeDelay, 1);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedWeaponRedWhenPlayerHasRedWeapon0PlayerShouldChangeWeaponToRed1_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setWeapon(redWeapons[0]);

    playerModel.changePlayerAtribute(special_reward_type::weaponRed);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                 redWeapons[1].type);
    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  redWeapons[1].fireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), redWeapons[1].fireTimeDelay, 1);
}

TEST_F(PlayerModelTestsClass, ChangePlayerAtribute_CollectedWeaponRedWhenPlayerHasRedWeaponMaxPlayerShouldntChangeWeapon_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setWeapon(redWeapons[4]);

    playerModel.changePlayerAtribute(special_reward_type::weaponRed);
    weapon        resultWeapon    = playerModel.getWeapon();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultWeapon.type,                 redWeapons[4].type);
    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  redWeapons[4].fireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), redWeapons[4].fireTimeDelay, 1);
}
