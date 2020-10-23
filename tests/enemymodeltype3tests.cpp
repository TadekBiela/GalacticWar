#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype3.hpp"
#include "../app/bulletmodel.hpp"
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType3Test : public EnemyModelType3
{
public:
    EnemyModelType3Test(
        QPointF position
    ) :
        EnemyModelType3(
            position
        )
    {}
    virtual ~EnemyModelType3Test() {}

    int getLevel() const {
        return m_level;
    }
    QPointF getPosition() const {
        return pos();
    }
    int getHealth() const {
        return m_health;
    }
    int getDamage() const {
        return m_damage;
    }
    int getDirection() const {
        return m_direction;
    }
    int getAnimationFrameXIdx() const {
        return m_animationFrameXIdx;
    }
    const QTimer& getFireTimer() const {
        return m_fireTimer;
    }
    const QTimer& getMoveTimer() const {
        return m_moveTimer;
    }
    const QTimer& getAnimationTimer() const {
        return m_animationTimer;
    }
    enemy_fire_side getFireSide() const {
        return m_fireSide;
    }
    enemy_rotation_direction getMoveRotationSide() const {
        return m_moveRotationSide;
    }
    int getMoveSlowFactor() const {
        return m_moveSlowFactor;
    }
    int getRotateMinBorder() const {
        return m_rotateMinBorder;
    }
    int getRotateMaxBorder() const {
        return m_rotateMaxBorder;
    }
    void setDirection(int direction) {
        m_direction = direction;
    }
};

class EnemyModelType3TestClass : public testing::Test
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_F(EnemyModelType3TestClass, Constructor_SpawnPositionIsOnLeftSideOfScene_ShouldSetXCoordinateAsAnimationFrameWightOffset)
{
    EnemyModelType3Test enemyModel(QPointF(2, 7));

    EXPECT_EQ(def::enemy3Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(def::animationFrameWight, resultPosition.x());
    EXPECT_FLOAT_EQ(7, resultPosition.y());
    EXPECT_EQ(def::enemy3MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy3BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy3MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy3FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(enemy_fire_side::right_cannon, enemyModel.getFireSide());
    EXPECT_EQ(enemy_rotation_direction::left, enemyModel.getMoveRotationSide());
    EXPECT_EQ(def::enemy3RotateLeftSideMinBorder, enemyModel.getRotateMinBorder());
    EXPECT_EQ(def::enemy3RotateLeftSideMaxBorder, enemyModel.getRotateMaxBorder());
}

TEST_F(EnemyModelType3TestClass, Constructor_SpawnPositionIsOnRightSideOfScene_ShouldSetXCoordinateAsSceneWidhtSubtractAnimationFrameWidthOffset)
{
    EnemyModelType3Test enemyModel(QPointF((def::halfSceneWight + 1), 0));

    EXPECT_EQ(def::enemy3Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ((def::sceneWight - def::animationFrameWight), resultPosition.x());
    EXPECT_FLOAT_EQ(0, resultPosition.y());
    EXPECT_EQ(def::enemy3MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy3BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy3MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy3FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(enemy_fire_side::right_cannon, enemyModel.getFireSide());
    EXPECT_EQ(enemy_rotation_direction::right, enemyModel.getMoveRotationSide());
    EXPECT_EQ(def::enemy3RotateRightSideMinBorder, enemyModel.getRotateMinBorder());
    EXPECT_EQ(def::enemy3RotateRightSideMaxBorder, enemyModel.getRotateMaxBorder());
}

TEST_F(EnemyModelType3TestClass, Fire_ExecutionOnce_ShouldCreateOneBulletOnTheRightSideOfEnemy)
{
    QPointF expectedEnemyPosition(def::animationFrameWight, 0);
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x() + def::enemy3FireSideOffset,
        expectedEnemyPosition.y()
    );
    QGraphicsScene mockScene;
    EnemyModelType3Test* enemy = new EnemyModelType3Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType3Test* resultEnemyModel = dynamic_cast<EnemyModelType3Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy3Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel->getType());
    QPointF resultBulletPosition = resultBulletModel->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition.x(), resultBulletPosition.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition.y(), resultBulletPosition.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy3BaseDamage, resultBulletModel->getDamage());
    EXPECT_EQ(def::down, resultBulletModel->rotation());
    delete enemy;
}

TEST_F(EnemyModelType3TestClass, Fire_ExecutionTwice_ShouldCreateTwoBulletsOnBothSidesOfEnemy)
{
    QPointF expectedEnemyPosition(def::animationFrameWight, 0);
    QPointF expectedBulletPosition1(
        expectedEnemyPosition.x() + def::enemy3FireSideOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedBulletPosition2(
        expectedEnemyPosition.x() - def::enemy3FireSideOffset,
        expectedEnemyPosition.y()
    );
    QGraphicsScene mockScene;
    EnemyModelType3Test* enemy = new EnemyModelType3Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();
    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType3Test* resultEnemyModel = dynamic_cast<EnemyModelType3Test*>(sceneItems[2]);
    EXPECT_EQ(def::enemy3Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBulletModel1 = dynamic_cast<BulletModel*>(sceneItems[1]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel1->getType());
    QPointF resultBulletPosition1 = resultBulletModel1->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition1.x(), resultBulletPosition1.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition1.y(), resultBulletPosition1.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy3BaseDamage, resultBulletModel1->getDamage());
    EXPECT_EQ(def::down, resultBulletModel1->rotation());
    BulletModel* resultBulletModel2 = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel2->getType());
    QPointF resultBulletPosition2 = resultBulletModel2->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition2.x(), resultBulletPosition2.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition2.y(), resultBulletPosition2.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy3BaseDamage, resultBulletModel2->getDamage());
    EXPECT_EQ(def::down, resultBulletModel2->rotation());
    delete enemy;
}

TEST_F(EnemyModelType3TestClass, Fire_ExecutionTwiceButEnemyRotateBetweenFire_ShouldCreateTwoBulletsOnBothSidesOfEnemySecondWithDifferentDirection)
{
    QPointF expectedEnemyPosition(def::animationFrameWight, 0);
    QPointF expectedBulletPosition1(
        expectedEnemyPosition.x() + def::enemy3FireSideOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedBulletPosition2(
        expectedEnemyPosition.x() - 9.90,
        expectedEnemyPosition.y() + 9.90
    );
    QGraphicsScene mockScene;
    EnemyModelType3Test* enemy = new EnemyModelType3Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();
    enemy->setDirection(135);
    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType3Test* resultEnemyModel = dynamic_cast<EnemyModelType3Test*>(sceneItems[2]);
    EXPECT_EQ(def::enemy3Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBulletModel1 = dynamic_cast<BulletModel*>(sceneItems[1]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel1->getType());
    QPointF resultBulletPosition1 = resultBulletModel1->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition1.x(), resultBulletPosition1.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition1.y(), resultBulletPosition1.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy3BaseDamage, resultBulletModel1->getDamage());
    EXPECT_EQ(def::down, resultBulletModel1->rotation());
    BulletModel* resultBulletModel2 = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel2->getType());
    QPointF resultBulletPosition2 = resultBulletModel2->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition2.x(), resultBulletPosition2.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition2.y(), resultBulletPosition2.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy3BaseDamage, resultBulletModel2->getDamage());
    EXPECT_EQ(135, resultBulletModel2->rotation());
    delete enemy;
}

typedef std::tr1::tuple<int, QPointF, QPointF, int> input_params;

class EnemyModelType3MoveParamTestClass : public testing::TestWithParam<input_params>
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_P(EnemyModelType3MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const QPointF startPosition = std::tr1::get<1>(GetParam());
    const QPointF expectedPosition = std::tr1::get<2>(GetParam());
    const int expectedDirection = std::tr1::get<3>(GetParam());
    QGraphicsScene stubScene;
    EnemyModelType3Test* enemyModel = new EnemyModelType3Test(startPosition);
    stubScene.addItem(enemyModel);

    for(int i = 0; i < numberOfMoveFuncExecutions; i++) {
        enemyModel->move();
    }

    QPointF resultPosition = enemyModel->getCenterPosition();
    EXPECT_NEAR(expectedPosition.x(), resultPosition.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedPosition.y(), resultPosition.y(), utdef::floatPrecision);
    EXPECT_EQ(expectedDirection, enemyModel->getDirection());
    delete enemyModel;
}

INSTANTIATE_TEST_SUITE_P(
    MovePath,
    EnemyModelType3MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            QPointF(0, 0),
            QPointF(def::animationFrameWight, def::enemy3MoveSlowFactor),
            def::down - def::enemy3RotateAngle
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                319
            ),
            def::down - (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor))
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 1,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                322
            ),
            def::down - (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 1))
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 2,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                325
            ),
            def::down - (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 2))
        ),
        std::tr1::make_tuple(
            40,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                373
            ),
            def::enemy3RotateLeftSideMinBorder
        ),
        std::tr1::make_tuple(
            41,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                376
            ),
            def::enemy3RotateLeftSideMinBorder + def::enemy3MinMoveSlowFactor
        ),
        std::tr1::make_tuple(
            80,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                493
            ),
            def::enemy3RotateLeftSideMaxBorder
        ),
        std::tr1::make_tuple(
            81,
            QPointF(0, 0),
            QPointF(
                def::animationFrameWight,
                496
            ),
            def::enemy3RotateLeftSideMaxBorder - def::enemy3MinMoveSlowFactor
        ),
        std::tr1::make_tuple(
            1,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(def::sceneWight - def::animationFrameWight, def::enemy3MoveSlowFactor),
            def::down + def::enemy3RotateAngle
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                319
            ),
            def::down + (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor))
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 1,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                322
            ),
            def::down + (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 1))
        ),
        std::tr1::make_tuple(
            def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 2,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                325
            ),
            def::down + (def::enemy3RotateAngle * (def::enemy3MoveSlowFactor - def::enemy3MinMoveSlowFactor + 2))
        ),
        std::tr1::make_tuple(
            40,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                373
            ),
            def::enemy3RotateRightSideMaxBorder
        ),
        std::tr1::make_tuple(
            41,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                376
            ),
            def::enemy3RotateRightSideMaxBorder - def::enemy3MinMoveSlowFactor
        ),
        std::tr1::make_tuple(
            80,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                493
            ),
            def::enemy3RotateRightSideMinBorder
        ),
        std::tr1::make_tuple(
            81,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::sceneWight - def::animationFrameWight,
                496
            ),
            def::enemy3RotateRightSideMinBorder + def::enemy3MinMoveSlowFactor
        )
    )
);
