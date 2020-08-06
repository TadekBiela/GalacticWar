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
