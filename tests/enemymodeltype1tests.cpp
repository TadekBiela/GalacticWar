#include <gtest/gtest.h>
#include "definitions.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/bullettype.hpp"
#include "../app/bulletmodel.hpp"
#include <QSignalSpy>
#include <QGraphicsScene>
#include <iostream>

class EnemyModelType1Test : public EnemyModelType1
{
public:
    explicit EnemyModelType1Test(QPointF position) :
                                 EnemyModelType1(position){}

    int           getLevel()             const { return m_level; }
    QPointF       getPosition()          const { return pos(); }
    int           getHealth()            const { return m_health; }
    int           getDamage()            const { return m_damage; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getFireTimer()         const { return m_fireTimer; }
    const QTimer& getMoveTimer()         const { return m_moveTimer; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
};

class EnemyModelType1TestClass : public testing::Test
{
};

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_CheckBuildModelCorrect_IsEqual)
{
    EnemyModelType1Test enemyModel(QPointF(2, 7));
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
    EXPECT_EQ(resultHealth,            2);
    EXPECT_EQ(resultDamage,            10);
    EXPECT_EQ(resultAnimationFrameIdx, 0);
    EXPECT_EQ(resultMoveTimerIsActive, true);
    EXPECT_EQ(resultFireTimerIsActive, true);
    EXPECT_EQ(resultAnimTimerIsActive, true);
    EXPECT_NEAR(resultMoveTime,        30, 1);
    EXPECT_NEAR(resultFireTime,        15, 1);
    EXPECT_NEAR(resultAnimationTime,    5, 1);
}

TEST_F(EnemyModelType1TestClass, Fire_CheckIfBulletIsAddedToScene_IsEqual)
{
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(2, 7));
    QGraphicsScene       mockScene;
    mockScene.addItem(enemyModel);

    enemyModel->fire();
    QList<QGraphicsItem*> sceneItems        = mockScene.items();
    EnemyModelType1Test*  resultEnemyModel  = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    BulletModel*          resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);

    EXPECT_EQ(resultEnemyModel->getLevel(),    1);
    EXPECT_EQ(resultEnemyModel->getPosition(), QPointF(2, 7));
    EXPECT_EQ(resultBulletModel->getType(),    bullet_type::enemyBullet);
    EXPECT_EQ(resultBulletModel->pos(),        QPointF(2, 7));
    EXPECT_EQ(resultBulletModel->getDamage(),  10);
    delete enemyModel;
}
