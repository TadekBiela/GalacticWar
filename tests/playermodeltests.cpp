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
    ::fire        getFireFuncPtr()   const { return m_fireFuncPtr; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
    void          setMoveDirection(QPointF moveDirection) { m_moveDirection = moveDirection; }
};

class PlayerModelTestsClass : public testing::Test
{
};

TEST_F(PlayerModelTestsClass, PlayerModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    PlayerModelTest playerModel;
    QPointF       resultMoveDirection = playerModel.getMoveDirection();
    weapon_type   resultWeapon        = playerModel.getWeapon();
    ::fire        resultFireFuncPtr   = playerModel.getFireFuncPtr();
    const QTimer& resultMoveTimer     = playerModel.getMoveTimer();
    const QTimer& resultFireTimer     = playerModel.getFireTimer();

    EXPECT_EQ(resultMoveDirection,        QPointF(def::halfSceneWight, def::halfSceneHeight));
    EXPECT_EQ(resultWeapon,               weapon_type::defaultWeapon);
    EXPECT_EQ(resultFireFuncPtr,          &defaultFireFunc);
    EXPECT_EQ(resultMoveTimer.isActive(), false);
    EXPECT_EQ(resultFireTimer.isActive(), false);
    EXPECT_FLOAT_EQ(resultMoveTimer.remainingTime(), -1);
    EXPECT_FLOAT_EQ(resultFireTimer.remainingTime(), -1);
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsUpOfCurrentPositionPlayerShouldFlyUpBy10Pixels_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight - 50));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_EQ(resultPosition,  QPointF(def::halfSceneWight, def::halfSceneHeight - 10));
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsEqualAsCurrentPlayerPositionShouldDontMove_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_EQ(resultPosition,  QPointF(def::halfSceneWight, def::halfSceneHeight));
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsOnly5PixLeftSideOfCurrentPlayerPositionShouldMoveOnly5pix_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight - 5, def::halfSceneHeight));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_EQ(resultPosition,  QPointF(def::halfSceneWight - 5, def::halfSceneHeight));
}

TEST_F(PlayerModelTestsClass, Move_MoveDirectionIsEqualAsDefMoveVectorLenghtDownOfCurrentPlayerPositionShouldMoveDown_IsEqual)
{
    PlayerModelTest playerModel;
    playerModel.setMoveDirection(QPointF(def::halfSceneWight, def::halfSceneHeight + def::moveVectorLength));

    playerModel.move();
    QPointF resultPosition = playerModel.getPosition();

    EXPECT_EQ(resultPosition,  QPointF(def::halfSceneWight, def::halfSceneHeight + def::moveVectorLength));
}
