#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype2.hpp"
#include "../app/bulletmodel.hpp"
#include <QSignalSpy>
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType2Test : public EnemyModelType2
{
public:
    EnemyModelType2Test(
        QPointF position
    ) :
        EnemyModelType2(
            position
        )
    {}
    virtual ~EnemyModelType2Test() {}

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
    enemy_rotation_direction getRotationDirection() const {
        return m_rotationDirection;
    }
    void setDirection(int direction) {
        m_direction = direction;
    }
};

class EnemyModelType2TestClass : public testing::Test
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

TEST_F(EnemyModelType2TestClass, Constructor_SpawnPositionIsOnLeftSideofScene_ShouldAddXCoordinateOffsetToStartPosition)
{
    EnemyModelType2Test enemyModel(QPointF(2, 7));

    EXPECT_EQ(def::enemy2Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(2 + def::enemy2XCoordinateOffset, resultPosition.x());
    EXPECT_FLOAT_EQ(7, resultPosition.y());
    EXPECT_EQ(def::enemy2MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy2BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::enemy2MinDirectionRange, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy2MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy2FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
}

TEST_F(EnemyModelType2TestClass, Constructor_SpawnPositionIsOnRightSideofScene_ShouldSubtractXCoordinateOffsetOfStartPosition)
{
    const QPointF startPosition(def::halfSceneWight + 1, 0);

    EnemyModelType2Test enemyModel(startPosition);

    EXPECT_EQ(def::enemy2Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(startPosition.x() - def::enemy2XCoordinateOffset, resultPosition.x());
    EXPECT_FLOAT_EQ(startPosition.y(), resultPosition.y());
    EXPECT_EQ(def::enemy2MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy2BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::enemy2MinDirectionRange, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy2MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy2FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
}

TEST_F(EnemyModelType2TestClass, Fire_EnemyMoveDirectionIsDown_ShouldCreateBulletWithDownMoveDirectionWithSameXCoordinateAndFrontOfEnemy)
{
    QPointF startEnemyPosition(100, 100);
    QPointF expectedEnemyPosition(
        (startEnemyPosition.x() + def::enemy2XCoordinateOffset),
        startEnemyPosition.y()
    );
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x(),
        (expectedEnemyPosition.y() + 28)
    );
    EnemyModelType2Test* enemyModel = new EnemyModelType2Test(startEnemyPosition);
    enemyModel->setDirection(def::down);
    QGraphicsScene mockScene;
    mockScene.addItem(enemyModel);
    //Change bullet pixmap size
    dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(3, 15);

    enemyModel->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType2Test* resultEnemyModel = dynamic_cast<EnemyModelType2Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy2Level, resultEnemyModel->getLevel());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyModel->getCenterPosition().x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyModel->getCenterPosition().y());
    BulletModel* resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel->getType());
    EXPECT_FLOAT_EQ(expectedBulletPosition.x(), resultBulletModel->getCenterPosition().x());
    EXPECT_FLOAT_EQ(expectedBulletPosition.y(), resultBulletModel->getCenterPosition().y());
    EXPECT_EQ(def::enemy2BaseDamage, resultBulletModel->getDamage());
    EXPECT_EQ(def::down, resultBulletModel->rotation());
    delete enemyModel;
}

TEST_F(EnemyModelType2TestClass, Fire_EnemyMoveDirectionIsMaxDirectionRange_ShouldCreateBulletWithSameDirectionSameXCoordinateAndFrontOfEnemy)
{
    QPointF startEnemyPosition(100, 100);
    QPointF expectedEnemyPosition(
        (startEnemyPosition.x() + def::enemy2XCoordinateOffset),
        startEnemyPosition.y()
    );
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x() - 19.80,
        (expectedEnemyPosition.y() + 19.80)
    );
    const int expectedBulletDirection = def::enemy2MinDirectionRange + 90;
    EnemyModelType2Test* enemyModel = new EnemyModelType2Test(startEnemyPosition);
    enemyModel->setDirection(expectedBulletDirection);
    QGraphicsScene mockScene;
    mockScene.addItem(enemyModel);
    //Change bullet pixmap size
    dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(3, 15);

    enemyModel->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType2Test* resultEnemyModel = dynamic_cast<EnemyModelType2Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy2Level, resultEnemyModel->getLevel());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyModel->getCenterPosition().x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyModel->getCenterPosition().y());
    BulletModel* resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel->getType());
    EXPECT_NEAR(expectedBulletPosition.x(), resultBulletModel->getCenterPosition().x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition.y(), resultBulletModel->getCenterPosition().y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy2BaseDamage, resultBulletModel->getDamage());
    EXPECT_EQ(expectedBulletDirection, resultBulletModel->rotation());
    delete enemyModel;
}

typedef std::tr1::tuple<int, QPointF, int> input_params;

class EnemyModelType2MoveParamTestClass : public testing::TestWithParam<input_params>
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

TEST_P(EnemyModelType2MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const QPointF expectedPosition = std::tr1::get<1>(GetParam());
    const int expectedDirection = std::tr1::get<2>(GetParam());
    QGraphicsScene stubScene;
    EnemyModelType2Test* enemyModel = new EnemyModelType2Test(QPointF(100, 0));
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
    EnemyModelType2MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            QPointF(153.47, 3.60),
            def::enemy2MinDirectionRange + 1
        ),
        std::tr1::make_tuple(
            45,
            QPointF(232.14, 203.30),
            def::down
        ),
        std::tr1::make_tuple(
            46,
            QPointF(232.05, 208.30),
            def::down + 1
        ),
        std::tr1::make_tuple(
            89,
            QPointF(150.00, 401.60),
            def::enemy2MaxDirectionRange - 1
        ),
        std::tr1::make_tuple(
            90,
            QPointF(146.46, 405.13),
            def::enemy2MaxDirectionRange
        ),
        std::tr1::make_tuple(
            91,
            QPointF(142.99, 408.73),
            def::enemy2MaxDirectionRange - 1
        ),
        std::tr1::make_tuple(
            180,
            QPointF(150, 810.26),
            def::enemy2MinDirectionRange
        ),
        std::tr1::make_tuple(
            181,
            QPointF(153.47, 813.86),
            def::enemy2MinDirectionRange + 1
        )
    )
);
