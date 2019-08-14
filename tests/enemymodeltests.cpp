#include <gtest/gtest.h>
#include "../app/enemymodel.hpp"
#include <QSignalSpy>

class EnemyModelTest : public EnemyModel
{
public:
    explicit EnemyModelTest(int     level,
                            QPointF position,
                            int     health,
                            int     damage,
                            int     moveTimeDelay,
                            int     fireTimeDelay) :
                            EnemyModel(level,
                                       position,
                                       health,
                                       damage,
                                       moveTimeDelay,
                                       fireTimeDelay){}

    int           getLevel()             const { return m_level; }
    QPointF       getPosition()          const { return pos(); }
    int           getHealth()            const { return m_health; }
    int           getDamage()            const { return m_damage; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getFireTimer()         const { return m_fireTimer; }
    const QTimer& getMoveTimer()         const { return m_moveTimer; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }

public slots: //dummy implementation - slots not tested in this class
    void fire(){}
    void move(){}
    void animation(){}
};

class EnemyModelTestsClass : public testing::Test
{
};

TEST_F(EnemyModelTestsClass, EnemyModelConstructor_CheckBuildModelCorrect_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    int     resultLevel             = enemyModel.getLevel();
    QPointF resultPosition          = enemyModel.getPosition();
    int     resultHealth            = enemyModel.getHealth();
    int     resultDamage            = enemyModel.getDamage();
    int     resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();
    bool    resultFireTimerIsActive = enemyModel.getMoveTimer().isActive();
    bool    resultMoveTimerIsActive = enemyModel.getFireTimer().isActive();
    bool    resultAnimTimerIsActive = enemyModel.getAnimationTimer().isActive();
    int     resultMoveTime          = enemyModel.getMoveTimer().remainingTime();
    int     resultFireTime          = enemyModel.getFireTimer().remainingTime();
    int     resultAnimationTime     = enemyModel.getAnimationTimer().remainingTime();

    EXPECT_EQ(resultLevel,             1);
    EXPECT_EQ(resultPosition,          QPointF(2, 7));
    EXPECT_EQ(resultHealth,            30);
    EXPECT_EQ(resultDamage,            15);
    EXPECT_EQ(resultAnimationFrameIdx, 0);
    EXPECT_EQ(resultMoveTimerIsActive, true);
    EXPECT_EQ(resultFireTimerIsActive, true);
    EXPECT_EQ(resultAnimTimerIsActive, true);
    EXPECT_NEAR(resultMoveTime,        20, 1);
    EXPECT_NEAR(resultFireTime,        10, 1);
    EXPECT_NEAR(resultAnimationTime,    5, 1);
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsLessThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, SIGNAL(destroyed(QPointF position, int level)));

    enemyModel.hit(13);
    int resultHealth = enemyModel.getHealth();

    EXPECT_EQ(resultHealth, 17);
    EXPECT_FALSE(signalDestroy.wait(10));
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsEqualThanHealth_IsZero)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, SIGNAL(destroyed(QPointF position, int level)));

    enemyModel.hit(30);
    int resultHealth = enemyModel.getHealth();

    EXPECT_EQ(resultHealth, 0);
    EXPECT_TRUE(signalDestroy.wait(10));
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsMoreThanHealth_IsZero)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, SIGNAL(destroyed(QPointF position, int level)));

    enemyModel.hit(43);
    int resultHealth = enemyModel.getHealth();

    EXPECT_EQ(resultHealth, 0);
    EXPECT_TRUE(signalDestroy.wait(10));
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsZeroThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, SIGNAL(destroyed(QPointF position, int level)));

    enemyModel.hit(0);
    int resultHealth = enemyModel.getHealth();

    EXPECT_EQ(resultHealth, 30);
    EXPECT_FALSE(signalDestroy.wait(10));
}
