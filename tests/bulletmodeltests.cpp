#include <gtest/gtest.h>
#include <utility>
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/bulletmodel.hpp"

class BulletModelTest : public BulletModel
{
public:
    BulletModelTest(QString name,
                    QPointF position,
                    int     damage,
                    int     direction,
                    int     moveTimeDelay)
                     : BulletModel(name,
                                   game_object_type::player_bullet,
                                   position,
                                   damage,
                                   direction,
                                   moveTimeDelay){}
    virtual ~BulletModelTest() {}
    void move()
    {
        BulletModel::move();
    }

    QPointF       getPosition()  const { return QGraphicsItem::pos(); }
    int           getDamage()    const { return m_damage; }
    int           getDirection() const { return m_direction; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }
};

class BulletModelTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(4, 20);
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    BulletModelTest bulletModel("bullet_default", QPointF(3, 5), 10, 5, 50);
    QPointF       resultPosition   = bulletModel.getPosition();
    int           resultDamage     = bulletModel.getDamage();
    int           resultDirection  = bulletModel.getDirection();
    const QTimer& resultMoveTimer  = bulletModel.getMoveTimer();

    EXPECT_EQ(resultDamage,                     10);
    EXPECT_EQ(resultDirection,                   5);
    EXPECT_EQ(resultMoveTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(), 50);
    EXPECT_FLOAT_EQ(resultPosition.x(),          1);
    EXPECT_FLOAT_EQ(resultPosition.y(),         -5);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectDirectionIsMoreThan360Deg_IsEqual)
{
    BulletModelTest bulletModel("bullet_default", QPointF(3, 5), 10, 450, 10);
    QPointF       resultPosition   = bulletModel.getPosition();
    int           resultDamage     = bulletModel.getDamage();
    int           resultDirection  = bulletModel.getDirection();
    const QTimer& resultMoveTimer  = bulletModel.getMoveTimer();

    EXPECT_EQ(resultDamage,                     10);
    EXPECT_EQ(resultDirection,                  90);
    EXPECT_EQ(resultMoveTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(), 10);
    EXPECT_FLOAT_EQ(resultPosition.x(),          1);
    EXPECT_FLOAT_EQ(resultPosition.y(),         -5);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectDirectionIsLessThan0Deg_IsEqual)
{
    BulletModelTest bulletModel("bullet_default", QPointF(3, 5), 10, -30, 10);
    QPointF       resultPosition   = bulletModel.getPosition();
    int           resultDamage     = bulletModel.getDamage();
    int           resultDirection  = bulletModel.getDirection();
    const QTimer& resultMoveTimer  = bulletModel.getMoveTimer();

    EXPECT_EQ(resultDamage,                      10);
    EXPECT_EQ(resultDirection,                  330);
    EXPECT_EQ(resultMoveTimer.isActive(),       true);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(),  10);
    EXPECT_FLOAT_EQ(resultPosition.x(),           1);
    EXPECT_FLOAT_EQ(resultPosition.y(),          -5);
}

TEST_F(BulletModelTestsClass, Start_CheckIfMoveTimerWillBeActive_IsEqual)
{
    BulletModelTest bulletModel("bullet_default", QPointF(3, 5), 10, -30, 10);

    bulletModel.start();
    const QTimer& resultMoveTimer = bulletModel.getMoveTimer();

    EXPECT_EQ(resultMoveTimer.isActive(), true);
}

TEST_F(BulletModelTestsClass, Stop_CheckIfMoveTimerWillBeNotActive_IsEqual)
{
    BulletModelTest bulletModel("bullet_default", QPointF(3, 5), 10, -30, 10);

    bulletModel.stop();
    const QTimer& resultMoveTimer = bulletModel.getMoveTimer();

    EXPECT_EQ(resultMoveTimer.isActive(), false);
}

class BulletModelTestsParamClass : public testing::TestWithParam<std::pair<int, QPointF>>
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(4, 20);
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_P(BulletModelTestsParamClass, Move_CheckChangingPositionDependenceOfDirection_IsEqual)
{
    std::pair<int, QPointF> inputParams      = GetParam();
    int                     direction        = inputParams.first;
    QPointF                 expectedPosition = inputParams.second;
    BulletModelTest         bulletModel("bullet_default",
                                        QPointF(300, 200),
                                        1,
                                        direction,
                                        10);

    bulletModel.move();
    QPointF resultPosition = bulletModel.getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
}

INSTANTIATE_TEST_SUITE_P(Move,
                         BulletModelTestsParamClass,
                         testing::Values(std::make_pair(    0, QPointF(298.00l, 180.00l)),   //Move to up
                                         std::make_pair(  360, QPointF(298.00l, 180.00l)),   //Move to up with 360 deg (should be equal as 0 deg)
                                         std::make_pair(  180, QPointF(298.00l, 200.00l)),   //Move to down
                                         std::make_pair(  270, QPointF(288.00l, 190.00l)),   //Move to left
                                         std::make_pair(   45, QPointF(305.07l, 182.93l)),   //Move to up-rigth 45 deg
                                         std::make_pair(  212, QPointF(292.70l, 198.48l)),   //Move to down-left 32 deg
                                         std::make_pair(  -14, QPointF(295.58l, 180.30l)),   //Move to up-left with -14 deg (should be equal as 346 deg)
                                         std::make_pair(  390, QPointF(303.00l, 181.34l)),   //Move to up-rigth with 390 deg (should be equal as 30 deg)
                                         std::make_pair(-1250, QPointF(296.26l, 199.85l))    //Move to down-left with -1250 deg (should be equal as 190 deg)
                                        ));
