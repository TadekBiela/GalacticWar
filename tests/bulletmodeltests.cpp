#include <gtest/gtest.h>
#include "../app/bullettype.hpp"
#include "../app/bulletmodel.hpp"

class BulletModelTest : public BulletModel
{
public:
    explicit BulletModelTest(bullet_type type,
                             QPointF     position,
                             int         damage,
                             int         direction,
                             int         moveTimeDelay) :
                             BulletModel(type,
                                         position,
                                         damage,
                                         direction,
                                         moveTimeDelay){}

    bullet_type getType() const        { return m_type; }
    QPointF getPosition() const        { return QGraphicsItem::pos(); }
    int getDamage() const              { return m_damage; }
    int getDirection() const           { return m_direction; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }
};

class BulletModelTestsClass : public testing::Test
{
};

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    BulletModelTest bulletModel(playerDefaultBullet, QPointF(3, 5), 10, 5, 50);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,           bullet_type::playerDefaultBullet);
    EXPECT_EQ(resultPosition,             QPointF(3, 5));
    EXPECT_EQ(resultDamage,               10);
    EXPECT_EQ(resultDirection,            5);
    EXPECT_EQ(resultMoveTimer.isActive(), true);
    EXPECT_NEAR(resultMoveTimer.remainingTime(), 50, 1);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectIfMoveTimeDelayIsWrong_IsEqual)
{
    BulletModelTest bulletModel(playerDefaultBullet, QPointF(3, 5), 10, 5, -10);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,                      bullet_type::playerDefaultBullet);
    EXPECT_EQ(resultPosition,                        QPointF(3, 5));
    EXPECT_EQ(resultDamage,                          10);
    EXPECT_EQ(resultDirection,                       5);
    EXPECT_EQ(resultMoveTimer.isActive(),            true);
    EXPECT_FLOAT_EQ(resultMoveTimer.remainingTime(), -1);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectDirectionIsMoreThan360Deg_IsEqual)
{
    BulletModelTest bulletModel(playerDefaultBullet, QPointF(3, 5), 10, 450, 10);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,           bullet_type::playerDefaultBullet);
    EXPECT_EQ(resultPosition,             QPointF(3, 5));
    EXPECT_EQ(resultDamage,               10);
    EXPECT_EQ(resultDirection,            90);
    EXPECT_EQ(resultMoveTimer.isActive(), true);
    EXPECT_NEAR(resultMoveTimer.remainingTime(), 10, 1);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectDirectionIsLessThan0Deg_IsEqual)
{
    BulletModelTest bulletModel(playerDefaultBullet, QPointF(3, 5), 10, -30, 10);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,           bullet_type::playerDefaultBullet);
    EXPECT_EQ(resultPosition,             QPointF(3, 5));
    EXPECT_EQ(resultDamage,               10);
    EXPECT_EQ(resultDirection,            330);
    EXPECT_EQ(resultMoveTimer.isActive(), true);
    EXPECT_NEAR(resultMoveTimer.remainingTime(), 10, 1);
}
