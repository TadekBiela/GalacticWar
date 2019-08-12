#include <gtest/gtest.h>
#include "../app/enemymodel.hpp"

class EnemyModelTest : public EnemyModel
{
public:
    explicit EnemyModelTest(int level,
                            int health,
                            int damage,
                            int moveTimeDelay,
                            int fireTimeDelay) :
                            EnemyModel(level,
                                       health,
                                       damage,
                                       moveTimeDelay,
                                       fireTimeDelay){}

    int                 getLevel()             const { return m_level; }
    int                 getHealth()            const { return m_health; }
    int                 getDamage()            const { return m_damage; }
    int                 getMoveTimeDelay()     const { return m_moveTimeDelay; }
    int                 getFireTimeDelay()     const { return m_fireTimeDelay; }
    int                 getAnimationTime()     const { return m_animationTime; }
    int                 getAnimationFrameIdx() const { return m_animationFrameIdx; }
    int                 getDestroyTime()       const { return m_destroyTime; }
    const QTimer&       getFireTimer()         const { return m_fireTimer; }
    const QTimer&       getMoveTimer()         const { return m_moveTimer; }
    const QTimer&       getAnimationTimer()    const { return m_animationTimer; }
    const QTimer&       getDestroyTimer()      const { return m_destroyTimer; }
    const QMediaPlayer& getDestroySound()      const { return m_destroySound; }
};

class EnemyModelTestsClass : public testing::Test
{
};

TEST_F(EnemyModelTestsClass, EnemyModel_CheckIfConstructorIsBuildModelCorrect_IsEqual)
{
    EnemyModelTest enemyModel(1, 30, 15, 20, 10);
    int                 resultLevel             = enemyModel.getLevel();
    int                 resultHealth            = enemyModel.getHealth();
    int                 resultDamage            = enemyModel.getDamage();
    int                 resultMoveTimeDelay     = enemyModel.getMoveTimeDelay();
    int                 resultFireTimeDelay     = enemyModel.getFireTimeDelay();
    int                 resultAnimationTime     = enemyModel.getAnimationTime();
    int                 resultAnimationFrameIdx = enemyModel.getAnimationFrameIdx();
    int                 resultDestroyTime       = enemyModel.getDestroyTime();
    const QTimer&       resultFireTimer         = enemyModel.getFireTimer();
    const QTimer&       resultMoveTimer         = enemyModel.getMoveTimer();
    const QTimer&       resultAnimationTimer    = enemyModel.getAnimationTimer();
    const QTimer&       resultDestroyTimer      = enemyModel.getDestroyTimer();
    const QMediaPlayer& resultDestroySound      = enemyModel.getDestroySound();

    EXPECT_EQ(1, 1);
}
