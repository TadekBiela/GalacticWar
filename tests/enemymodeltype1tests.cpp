#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype1.hpp"
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

    int           getLevel()              const { return m_level; }
    QPointF       getPosition()           const { return pos(); }
    int           getHealth()             const { return m_health; }
    int           getDamage()             const { return m_damage; }
    int           getDirection()          const { return m_direction; }
    int           getAnimationFrameXIdx() const { return m_animationFrameXIdx; }
    const QTimer& getFireTimer()          const { return m_fireTimer; }
    const QTimer& getMoveTimer()          const { return m_moveTimer; }
    const QTimer& getAnimationTimer()     const { return m_animationTimer; }
};

class EnemyModelType1TestClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_CheckBuildModelCorrectDirectionShouldBeDown_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);

    EnemyModelType1Test enemyModel(QPointF(2, 7), randomGenerator);
    int           resultLevel              = enemyModel.getLevel();
    QPointF       resultPosition           = enemyModel.getPosition();
    int           resultHealth             = enemyModel.getHealth();
    int           resultDamage             = enemyModel.getDamage();
    int           resultDirection          = enemyModel.getDirection();
    int           resultAnimationFrameXIdx = enemyModel.getAnimationFrameXIdx();
    const QTimer& resultMoveTimer          = enemyModel.getMoveTimer();
    const QTimer& resultFireTimer          = enemyModel.getFireTimer();
    const QTimer& resultAnimTimer          = enemyModel.getAnimationTimer();

    EXPECT_EQ(resultLevel,                      1);
    EXPECT_EQ(resultHealth,                     50);
    EXPECT_EQ(resultDamage,                     10);
    EXPECT_EQ(resultDirection,                  180);
    EXPECT_EQ(resultAnimationFrameXIdx,         0);
    EXPECT_EQ(resultMoveTimer.isActive(),       false);
    EXPECT_EQ(resultFireTimer.isActive(),       false);
    EXPECT_EQ(resultAnimTimer.isActive(),       false);
    EXPECT_FLOAT_EQ(resultMoveTimer.interval(), 80);
    EXPECT_FLOAT_EQ(resultFireTimer.interval(), 1000);
    EXPECT_FLOAT_EQ(resultAnimTimer.interval(), 100);
    EXPECT_FLOAT_EQ(resultPosition.x(),         -30);
    EXPECT_FLOAT_EQ(resultPosition.y(),         -25);
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
    randomGenerator->setRandomGeneratorFakeResult(0);
    QGraphicsScene       mockScene;
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(QPointF(2, 7), randomGenerator);
    mockScene.addItem(enemyModel);
    dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(3, 15); //Change bullet pixmap size

    enemyModel->fire();
    QList<QGraphicsItem*> sceneItems        = mockScene.items();
    EnemyModelType1Test*  resultEnemyModel  = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    BulletModel*          resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);

    EXPECT_EQ(resultEnemyModel->getLevel(),       1);
    EXPECT_FLOAT_EQ(resultEnemyModel->pos().x(),  -30);
    EXPECT_FLOAT_EQ(resultEnemyModel->pos().y(),  -25);
    EXPECT_EQ(resultBulletModel->getName(),       "bullet_enemy");
    EXPECT_FLOAT_EQ(resultBulletModel->pos().x(), 1);
    EXPECT_FLOAT_EQ(resultBulletModel->pos().y(), 27);
    EXPECT_EQ(resultBulletModel->getDamage(),     10);
    delete enemyModel;
    delete randomGenerator;
}

TEST_F(EnemyModelType1TestClass, Move_PositionIsOnLeftSideOfSceneCheckIfEnemyMoveToDown_IsEqual)
{
    RandomGeneratorStub* randomGenerator = new RandomGeneratorStub();
    randomGenerator->setRandomGeneratorFakeResult(0);
    QPointF              expectedPosition(168.00l, 178.00l);
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
    QPointF              expectedPosition(169.74l, 177.85l);
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
    QPointF              expectedPosition(418.00l, -22.00l);
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
    QPointF              expectedPosition(416.26l, -22.15l);
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
