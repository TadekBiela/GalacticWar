#include <gtest/gtest.h>
#include "../app/enemymodel.hpp"

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

    int                 getLevel()             const { return m_level; }
    QPointF             getPosition()          const { return pos(); }
    int                 getHealth()            const { return m_health; }
    int                 getDamage()            const { return m_damage; }
    int                 getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer&       getFireTimer()         const { return m_fireTimer; }
    const QTimer&       getMoveTimer()         const { return m_moveTimer; }
    const QTimer&       getAnimationTimer()    const { return m_animationTimer; }
};

class EnemyModelTestsClass : public testing::Test
{
};

TEST_F(EnemyModelTestsClass, EnemyModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
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
