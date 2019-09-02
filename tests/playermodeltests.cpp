#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/playermodel.hpp"

class PlayerModelTest : public PlayerModel
{
public:
    explicit PlayerModelTest() {}

    QPointF       getMoveDirection() const { return m_moveDirection; }
    weapon_type   getWeapon()        const { return m_weapon; }
    ::fire        getFireFuncPtr()   const { return m_fireFuncPtr; }
    const QTimer& getMoveTimer()     const { return m_moveTimer; }
    const QTimer& getFireTimer()     const { return m_fireTimer; }
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
