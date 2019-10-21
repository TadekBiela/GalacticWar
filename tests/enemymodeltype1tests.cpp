#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/bullettype.hpp"
#include "../app/bulletmodel.hpp"
#include <QSignalSpy>
#include <QGraphicsScene>

class EnemyModelType1Test : public EnemyModelType1
{
public:
    EnemyModelType1Test(QPointF           position,
                        IRandomGenerator* generator)
                         : EnemyModelType1(position,
                                           generator){}
    virtual ~EnemyModelType1Test() {}

    int           getLevel()             const { return m_level; }
    QPointF       getPosition()          const { return pos(); }
    int           getHealth()            const { return m_health; }
    int           getDamage()            const { return m_damage; }
    int           getDirection()         const { return m_direction; }
    int           getAnimationFrameIdx() const { return m_animationFrameIdx; }
    const QTimer& getFireTimer()         const { return m_fireTimer; }
    const QTimer& getMoveTimer()         const { return m_moveTimer; }
    const QTimer& getAnimationTimer()    const { return m_animationTimer; }
};

class EnemyModelType1TestClass : public testing::Test
{
};

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_CheckBuildModelCorrectDirectionShouldBeDown_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);

    EnemyModelType1Test enemyModel(QPointF(2, 7), randomGenerator);
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
    EXPECT_EQ(resultHealth,            2);
    EXPECT_EQ(resultDamage,            10);
    EXPECT_EQ(resultDirection,         180);
    EXPECT_EQ(resultAnimationFrameIdx, 0);
    EXPECT_EQ(resultMoveTimerIsActive, false);
    EXPECT_EQ(resultFireTimerIsActive, false);
    EXPECT_EQ(resultAnimTimerIsActive, false);
    EXPECT_NEAR(resultMoveTime,        30, 1);
    EXPECT_NEAR(resultFireTime,        15, 1);
    EXPECT_NEAR(resultAnimationTime,    5, 1);
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsRightSideOfSceneDirectionCalculationShouldBe180_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);

    EnemyModelType1Test enemyModel(QPointF(450, 0), randomGenerator);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(resultDirection, 180);
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsRightSideOfSceneDirectionCalculationShouldBe190_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(1);

    EnemyModelType1Test enemyModel(QPointF(450, 0), randomGenerator);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(resultDirection, 190);
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsLeftSideOfSceneDirectionCalculationShouldBe180_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);

    EnemyModelType1Test enemyModel(QPointF(250, 0), randomGenerator);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(resultDirection, 180);
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsLeftSideOfSceneDirectionCalculationShouldBe170_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(1);

    EnemyModelType1Test enemyModel(QPointF(250, 0), randomGenerator);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(resultDirection, 170);
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Fire_CheckIfBulletIsAddedToScene_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    QGraphicsScene       mockScene;
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(2, 7), randomGenerator);
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
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Move_PositionIsOnLeftSideOfSceneCheckIfEnemyMoveToDown_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);
    QPointF              expectedPosition(200.00l, 210.00l);
    QGraphicsScene       mockScene(0, 0, 600, 800);
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(200, 200), randomGenerator);
    mockScene.addItem(enemyModel);

    enemyModel->move();
    QPointF resultPosition = enemyModel->getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Move_PositionIsOnLeftSideOfSceneCheckIfEnemyMoveToRight_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(1);
    QPointF              expectedPosition(201.74l, 209.85l);
    QGraphicsScene       mockScene(0, 0, 600, 800);
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(200, 200), randomGenerator);
    mockScene.addItem(enemyModel);

    enemyModel->move();
    QPointF resultPosition = enemyModel->getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Move_PositionIsOnRightSideOfSceneCheckIfEnemyMoveToDown_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);
    QPointF              expectedPosition(450.00l, 10.00l);
    QGraphicsScene       mockScene(0, 0, 600, 800);
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(450, 0), randomGenerator);
    mockScene.addItem(enemyModel);

    enemyModel->move();
    QPointF resultPosition = enemyModel->getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Move_PositionIsOnRightSideOfSceneCheckIfEnemyMoveToLeft_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(1);
    QPointF              expectedPosition(448.26l, 9.85l);
    QGraphicsScene       mockScene(0, 0, 600, 800);
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(450, 0), randomGenerator);
    mockScene.addItem(enemyModel);

    enemyModel->move();
    QPointF resultPosition = enemyModel->getPosition();

    EXPECT_NEAR(resultPosition.x(), expectedPosition.x(), 0.01);
    EXPECT_NEAR(resultPosition.y(), expectedPosition.y(), 0.01);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Animation_CheckIfAnimationFrameIdxWasIncreasedBy1_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(450, 0), randomGenerator);

    enemyModel->animation();
    int resultAnimationFrameIdx = enemyModel->getAnimationFrameIdx();

    EXPECT_EQ(resultAnimationFrameIdx, 1);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Animation_AnimationFrameIdxPointsToLastFrameCheckIfResetTo0_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(450, 0), randomGenerator);

    enemyModel->animation();
    enemyModel->animation();
    enemyModel->animation();
    int resultAnimationFrameIdx = enemyModel->getAnimationFrameIdx();
    enemyModel->animation();
    enemyModel->animation();
    int resultAnimationFrameIdxReset = enemyModel->getAnimationFrameIdx();

    EXPECT_EQ(resultAnimationFrameIdx,      3);
    EXPECT_EQ(resultAnimationFrameIdxReset, 0);
    delete enemyModel;
    delete randomGenerator;
}
