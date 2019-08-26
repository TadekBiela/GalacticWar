#include <gtest/gtest.h>
#include "utdefinitions.hpp"
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
    int           getDirection()         const { return m_direction; }
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
    int     resultDirection         = enemyModel.getDirection();
    int     resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();
    bool    resultFireTimerIsActive = enemyModel.getMoveTimer().isActive();
    bool    resultMoveTimerIsActive = enemyModel.getFireTimer().isActive();
    bool    resultAnimTimerIsActive = enemyModel.getAnimationTimer().isActive();
    int     resultMoveTime          = enemyModel.getMoveTimer().interval();
    int     resultFireTime          = enemyModel.getFireTimer().interval();
    int     resultAnimationTime     = enemyModel.getAnimationTimer().interval();

    EXPECT_EQ(resultLevel,             1);
    EXPECT_EQ(resultPosition,          QPointF(2, 7));
    EXPECT_EQ(resultHealth,            30);
    EXPECT_EQ(resultDamage,            15);
    EXPECT_EQ(resultDirection,         0);
    EXPECT_EQ(resultAnimationFrameIdx, 0);
    EXPECT_EQ(resultMoveTimerIsActive, false);
    EXPECT_EQ(resultFireTimerIsActive, false);
    EXPECT_EQ(resultAnimTimerIsActive, false);
    EXPECT_NEAR(resultMoveTime,        20, 1);
    EXPECT_NEAR(resultFireTime,        10, 1);
    EXPECT_NEAR(resultAnimationTime,    5, 1);
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsLessThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, &EnemyModelTest::destroyed);
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel.hit(13);
    int resultHealth      = enemyModel.getHealth();
    int resultSignalCount = signalDestroy.count();

    EXPECT_EQ(resultHealth,      17);
    EXPECT_EQ(resultSignalCount, 0);
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsEqualThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, &EnemyModelTest::destroyed);
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel.hit(30);
    int             resultHealth      = enemyModel.getHealth();
    int             resultSignalCount = signalDestroy.count();
    QList<QVariant> resultSignal      = signalDestroy.takeFirst();

    EXPECT_EQ(resultHealth,                  0);
    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(2, 7));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsMoreThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, &EnemyModelTest::destroyed);
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel.hit(43);
    int             resultHealth      = enemyModel.getHealth();
    int             resultSignalCount = signalDestroy.count();
    QList<QVariant> resultSignal      = signalDestroy.takeFirst();

    EXPECT_EQ(resultHealth,                  0);
    EXPECT_EQ(resultSignalCount,             1);
    EXPECT_EQ(resultSignal.at(0).toPointF(), QPointF(2, 7));
    EXPECT_EQ(resultSignal.at(1).toInt(),    1);
}

TEST_F(EnemyModelTestsClass, Hit_CheckIfDamageValueIsZeroThanHealth_IsEqual)
{
    EnemyModelTest enemyModel(1, QPointF(2, 7), 30, 15, 20, 10);
    QSignalSpy     signalDestroy(&enemyModel, &EnemyModelTest::destroyed);
    signalDestroy.wait(utdef::minSignalTimeDelay);

    enemyModel.hit(0);
    int resultHealth      = enemyModel.getHealth();
    int resultSignalCount = signalDestroy.count();

    EXPECT_EQ(resultHealth,      30);
    EXPECT_EQ(resultSignalCount, 0);
}
