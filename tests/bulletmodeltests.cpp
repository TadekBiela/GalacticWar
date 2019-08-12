#include <gtest/gtest.h>
#include <utility>
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

class BulletModelTestsParamClass : public testing::TestWithParam<std::pair<int, QPointF>>
{
};

TEST_P(BulletModelTestsParamClass, Move_CheckChangingPositionDependenceOfDirection_IsEqual)
{
    std::pair<int, QPointF> inputParams      = GetParam();
    int                     direction        = inputParams.first;
    QPointF                 expectedPosition = inputParams.second;
    BulletModelTest         bulletModel(playerDefaultBullet,
                                        QPointF(300, 200),
                                        1,
                                        direction,
                                        10);

    bulletModel.move();
    QPointF resultPosition = bulletModel.getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
}

INSTANTIATE_TEST_CASE_P(,
                        BulletModelTestsParamClass,
                        testing::Values(std::make_pair(    0, QPointF(300.00l, 190.00l)),   //Move to up
                                        std::make_pair(  360, QPointF(300.00l, 190.00l)),   //Move to up with 360 deg (should be equal as 0 deg)
                                        std::make_pair(  180, QPointF(300.00l, 210.00l)),   //Move to down
                                        std::make_pair(  270, QPointF(290.00l, 200.00l)),   //Move to left
                                        std::make_pair(   45, QPointF(307.07l, 192.93l)),   //Move to up-rigth 45 deg
                                        std::make_pair(  212, QPointF(294.70l, 208.48l)),   //Move to down-left 32 deg
                                        std::make_pair(  -14, QPointF(297.58l, 190.30l)),   //Move to up-left with -14 deg (should be equal as 346 deg)
                                        std::make_pair(  390, QPointF(305.00l, 191.34l)),   //Move to up-rigth with 390 deg (should be equal as 30 deg)
                                        std::make_pair(-1250, QPointF(298.26l, 209.85l))    //Move to down-left with -1250 deg (should be equal as 190 deg)
                                       ));
