#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"

class PlayerModelTest : public PlayerModel
{
public:
    explicit PlayerModelTest() {}

    QPointF       getPosition()      const { return QGraphicsItem::pos(); }
    QPointF       getMoveDirection() const { return m_moveDirection; }
    weapon_type   getWeapon()        const { return m_weapon; }
    int           getDamage()        const { return m_damage; }
    ::fire        getFireFuncPtr()   const { return m_fireFuncPtr; }
    int           getMoveTimeDelay() const { return m_moveTimeDelay; }
    int           getFireTimeDelay() const { return m_fireTimeDelay; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
    void          setMoveDirection(QPointF moveDirection) { m_moveDirection = moveDirection; }
    void          setFireTimeDelay(int fireTimeDelay)     { m_fireTimeDelay = fireTimeDelay; }
    void          startFireTimer()                        { m_fireTimer.start(); }
};

class PlayerModelTestsClass : public testing::Test
{
};

TEST_F(PlayerModelTestsClass, PlayerModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    QPointF expectedPosition(QPointF(def::halfSceneWight, def::halfSceneHeight));

    PlayerModelTest playerModel;
    QPointF       resultMoveDirection = playerModel.getMoveDirection();
    QPointF       resultPosition      = playerModel.getPosition();
    weapon_type   resultWeapon        = playerModel.getWeapon();
    int           resultDamage        = playerModel.getDamage();
    ::fire        resultFireFuncPtr   = playerModel.getFireFuncPtr();
    int           resultFireMoveDelay = playerModel.getMoveTimeDelay();
    int           resultFireTimeDelay = playerModel.getFireTimeDelay();
    const QTimer& resultMoveTimer     = playerModel.getMoveTimer();
    const QTimer& resultFireTimer     = playerModel.getFireTimer();

    EXPECT_EQ(resultMoveDirection,        QPointF(def::halfSceneWight, def::halfSceneHeight));
    EXPECT_EQ(resultWeapon,               weapon_type::defaultWeapon);
    EXPECT_EQ(resultDamage,               def::defaultPlayerDamage);
    EXPECT_EQ(resultFireFuncPtr,          &defaultFireFunc);
    EXPECT_EQ(resultFireMoveDelay,        def::defaultPlayerMoveTimeDelay);
    EXPECT_EQ(resultFireTimeDelay,        def::defaultPlayerFireTimeDelay);
    EXPECT_EQ(resultMoveTimer.isActive(), true);
    EXPECT_EQ(resultFireTimer.isActive(), false);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(), def::defaultPlayerMoveTimeDelay);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(), def::defaultPlayerFireTimeDelay);
    EXPECT_NEAR(    resultMoveTimer.remainingTime(), def::defaultPlayerMoveTimeDelay, 1);
    EXPECT_FLOAT_EQ(resultFireTimer.remainingTime(), -1);
    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsUpOfCurrentPositionPlayerShouldFlyUpBy10Pixels_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight - 10);
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight - 50));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsEqualAsCurrentPlayerPositionShouldDontMove_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight);
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsOnly5PixLeftSideOfCurrentPlayerPositionShouldMoveOnly5pix_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight);
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight - 5, def::halfSceneHeight));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsEqualAsDefMoveVectorLenghtDownOfCurrentPlayerPositionShouldMoveDown_IsEqual)
{
    QPointF         expectedPosition(def::halfSceneWight, def::halfSceneHeight + def::moveVectorLength);
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight + def::moveVectorLength));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_FLOAT_EQ(resultPosition.x(), expectedPosition.x());
    EXPECT_FLOAT_EQ(resultPosition.y(), expectedPosition.y());
}

TEST_F(PlayerModelTestsClass, StartFire_CheckCorrectWorkingWithDefaultConfiguration_IsEqual)
{
    PlayerModelTest playerModel;

    playerModel.startFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  def::defaultPlayerFireTimeDelay);
    EXPECT_NEAR(resultFireTimer.remainingTime(), def::defaultPlayerFireTimeDelay, 0.01);
}

TEST_F(PlayerModelTestsClass, StartFire_CheckCorrectWorkingWithChangedFireTimeDelay_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setFireTimeDelay(8);

    playerModel.startFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultFireTimer.isActive(),        true);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),  8);
    EXPECT_NEAR(resultFireTimer.remainingTime(), 8, 0.01);
}

TEST_F(PlayerModelTestsClass, StopFire_CheckCorrectWorking_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.startFireTimer();

    playerModel.stopFire();
    const QTimer& resultFireTimer = playerModel.getFireTimer();

    EXPECT_EQ(resultFireTimer.isActive(),            false);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(),      def::defaultPlayerFireTimeDelay);
    EXPECT_FLOAT_EQ(resultFireTimer.remainingTime(), -1);
}
