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
    int getMoveTimeDelay() const       { return m_moveTimeDelay; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }

    bool operator==(const BulletModelTest& bulletModelTest)
    {
        if(this->m_type == bulletModelTest.m_type)
            if(this->m_damage == bulletModelTest.m_damage)
                if(this->m_direction == bulletModelTest.m_direction)
                    if(this->m_moveTimeDelay == bulletModelTest.m_moveTimeDelay)
                        return true;
        return false;
    }
};

class BulletModelTestsClass : public testing::Test
{
};

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    BulletModelTest bulletModel(playerDefaultBullet, QPointF(3, 5), 10, 5, 30);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    int           resultMoveTimeDelay = bulletModel.getMoveTimeDelay();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,                      bullet_type::playerDefaultBullet);
    EXPECT_EQ(resultPosition,                        QPointF(3, 5));
    EXPECT_EQ(resultDamage,                          10);
    EXPECT_EQ(resultDirection,                       5);
    EXPECT_EQ(resultMoveTimeDelay,                   50);
    EXPECT_EQ(resultMoveTimer.isActive(),            true);
    EXPECT_FLOAT_EQ(resultMoveTimer.remainingTime(), 50);
}

TEST_F(BulletModelTestsClass, BulletModel_CheckIfConstructorIsBuildModelCorrectWithZeroMoveTimeDelay_IsEqual)
{
    BulletModelTest bulletModel(playerYellowBullet, QPointF(3, 5), 10, 5, 30);
    bullet_type   resultBulletType    = bulletModel.getType();
    QPointF       resultPosition      = bulletModel.getPosition();
    int           resultDamage        = bulletModel.getDamage();
    int           resultDirection     = bulletModel.getDirection();
    int           resultMoveTimeDelay = bulletModel.getMoveTimeDelay();
    const QTimer& resultMoveTimer     = bulletModel.getMoveTimer();

    EXPECT_EQ(resultBulletType,                      bullet_type::playerYellowBullet);
    EXPECT_EQ(resultPosition,                        QPointF(3, 5));
    EXPECT_EQ(resultDamage,                          10);
    EXPECT_EQ(resultDirection,                       5);
    EXPECT_EQ(resultMoveTimeDelay,                   0);
    EXPECT_EQ(resultMoveTimer.isActive(),            false);
    EXPECT_FLOAT_EQ(resultMoveTimer.remainingTime(), -1);
}
