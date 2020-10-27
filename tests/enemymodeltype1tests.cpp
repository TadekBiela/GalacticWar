#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/bulletmodel.hpp"
#include <QSignalSpy>
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType1Test : public EnemyModelType1
{
public:
    EnemyModelType1Test(
        QPointF position,
        IRandomGenerator* generator
    ) :
        EnemyModelType1(
            position,
            generator
        )
    {}
    virtual ~EnemyModelType1Test() {}

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
    int getAnimationFrameYIdx() const {
        return m_animationFrameYIdx;
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
};

class EnemyModelType1TestClass : public testing::Test
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

TEST_F(EnemyModelType1TestClass, Constructor_SpawnPositionIsOnLeftSideOfSceneDirectionGeneratedIsDown_ShouldSetDirectionToDown)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));

    EnemyModelType1Test enemy(
        QPointF(2, 0),
        generatorStub
    );

    EXPECT_EQ(def::enemy1Level, enemy.getLevel());
    QPointF resultPosition = enemy.getCenterPosition();
    EXPECT_FLOAT_EQ(2, resultPosition.x());
    EXPECT_FLOAT_EQ(0, resultPosition.y());
    EXPECT_EQ(def::enemy1MaxHealthPoints, enemy.getHealth());
    EXPECT_EQ(def::enemy1BaseDamage, enemy.getDamage());
    EXPECT_EQ(def::down, enemy.getDirection());
    EXPECT_EQ(0, enemy.getAnimationFrameXIdx());
    EXPECT_EQ(0, enemy.getAnimationFrameYIdx());
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemy.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Constructor_SpawnPositionIsOnLeftSideOfSceneDirectionGeneratedIsRight_ShouldSetDirectionToEnemy1Right)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));

    EnemyModelType1Test enemy(
        QPointF(2, 0),
        generatorStub
    );

    EXPECT_EQ(def::enemy1Level, enemy.getLevel());
    QPointF resultPosition = enemy.getCenterPosition();
    EXPECT_FLOAT_EQ(2, resultPosition.x());
    EXPECT_FLOAT_EQ(0, resultPosition.y());
    EXPECT_EQ(def::enemy1MaxHealthPoints, enemy.getHealth());
    EXPECT_EQ(def::enemy1BaseDamage, enemy.getDamage());
    EXPECT_EQ(def::enemy1RightMoveDirection, enemy.getDirection());
    EXPECT_EQ(0, enemy.getAnimationFrameXIdx());
    EXPECT_EQ(2, enemy.getAnimationFrameYIdx());
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemy.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Constructor_SpawnPositionIsOnRightSideOfSceneDirectionGeneratedIsDown_ShouldSetDirectionToDown)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));

    EnemyModelType1Test enemy(
        QPointF(def::halfSceneWight + 1, 0),
        generatorStub
    );

    EXPECT_EQ(def::enemy1Level, enemy.getLevel());
    QPointF resultPosition = enemy.getCenterPosition();
    EXPECT_FLOAT_EQ(def::halfSceneWight + 1, resultPosition.x());
    EXPECT_FLOAT_EQ(0, resultPosition.y());
    EXPECT_EQ(def::enemy1MaxHealthPoints, enemy.getHealth());
    EXPECT_EQ(def::enemy1BaseDamage, enemy.getDamage());
    EXPECT_EQ(def::down, enemy.getDirection());
    EXPECT_EQ(0, enemy.getAnimationFrameXIdx());
    EXPECT_EQ(0, enemy.getAnimationFrameYIdx());
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemy.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Constructor_SpawnPositionIsOnRightSideOfSceneDirectionGeneratedIsLeft_ShouldSetDirectionToEnemy1Left)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));

    EnemyModelType1Test enemy(
        QPointF(def::halfSceneWight + 1, 0),
        generatorStub
    );

    EXPECT_EQ(def::enemy1Level, enemy.getLevel());
    QPointF resultPosition = enemy.getCenterPosition();
    EXPECT_FLOAT_EQ(def::halfSceneWight + 1, resultPosition.x());
    EXPECT_FLOAT_EQ(0, resultPosition.y());
    EXPECT_EQ(def::enemy1MaxHealthPoints, enemy.getHealth());
    EXPECT_EQ(def::enemy1BaseDamage, enemy.getDamage());
    EXPECT_EQ(def::enemy1LeftMoveDirection, enemy.getDirection());
    EXPECT_EQ(0, enemy.getAnimationFrameXIdx());
    EXPECT_EQ(1, enemy.getAnimationFrameYIdx());
    const QTimer& resultMoveTimer = enemy.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemy.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy1FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemy.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Fire_EnemyDirectionIsDown_ShouldAddBulletToSceneWithDownDirection)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    //0 - enemy direction set on def::down
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));
    QGraphicsScene mockScene;
    QPointF expectedEnemyPosition(100, 100);
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x(),
        expectedEnemyPosition.y() + 28
    );
    EnemyModelType1Test* enemy = new EnemyModelType1Test(
        expectedEnemyPosition,
        generatorStub
    );
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType1Test* resultEnemy = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy1Level, resultEnemy->getLevel());
    QPointF resultEnemyPosition = resultEnemy->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBullet = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBullet->getType());
    QPointF resultBulletPosition = resultBullet->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedBulletPosition.x(), resultBulletPosition.x());
    EXPECT_FLOAT_EQ(expectedBulletPosition.y(), resultBulletPosition.y());
    EXPECT_EQ(def::enemy1BaseDamage, resultBullet->getDamage());
    EXPECT_EQ(def::down, resultBullet->rotation());
    delete enemy;
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Fire_EnemyDirectionIsRight_ShouldAddBulletToSceneWithEnemyRightDirection)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    //1 and position on the left side of scene
    //- enemy direction set on def::enemy1RightMoveDirection
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));
    QGraphicsScene mockScene;
    QPointF expectedEnemyPosition(100, 100);
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x() + 4.86,
        expectedEnemyPosition.y() + 27.57
    );
    EnemyModelType1Test* enemy = new EnemyModelType1Test(
        expectedEnemyPosition,
        generatorStub
    );
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType1Test* resultEnemy = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy1Level, resultEnemy->getLevel());
    QPointF resultEnemyPosition = resultEnemy->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBullet = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBullet->getType());
    QPointF resultBulletPosition = resultBullet->getCenterPosition();
    EXPECT_NEAR(
        expectedBulletPosition.x(),
        resultBulletPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedBulletPosition.y(),
        resultBulletPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy1BaseDamage, resultBullet->getDamage());
    EXPECT_EQ(def::enemy1RightMoveDirection, resultBullet->rotation());
    delete enemy;
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Fire_EnemyDirectionIsLeft_ShouldAddBulletToSceneWithEnemyLeftDirection)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    //1 and position on the right side of scene
    //- enemy direction set on def::enemy1LeftMoveDirection
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));
    QGraphicsScene mockScene;
    QPointF expectedEnemyPosition(def::halfSceneWight + 1, 100);
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x() - 4.86,
        expectedEnemyPosition.y() + 27.57
    );
    EnemyModelType1Test* enemy = new EnemyModelType1Test(
        expectedEnemyPosition,
        generatorStub
    );
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType1Test* resultEnemy = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy1Level, resultEnemy->getLevel());
    QPointF resultEnemyPosition = resultEnemy->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBullet = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBullet->getType());
    QPointF resultBulletPosition = resultBullet->getCenterPosition();
    EXPECT_NEAR(
        expectedBulletPosition.x(),
        resultBulletPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedBulletPosition.y(),
        resultBulletPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy1BaseDamage, resultBullet->getDamage());
    EXPECT_EQ(def::enemy1LeftMoveDirection, resultBullet->rotation());
    delete enemy;
    delete generatorStub;
}

typedef std::tr1::tuple<int, int, QPointF, QPointF, int> input_params;

class EnemyModelType1MoveParamTestClass : public testing::TestWithParam<input_params>
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

TEST_P(EnemyModelType1MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const int randomGeneratedResult = std::tr1::get<1>(GetParam());
    const QPointF startPosition = std::tr1::get<2>(GetParam());
    const QPointF expectedPosition = std::tr1::get<3>(GetParam());
    const int expectedDirection = std::tr1::get<4>(GetParam());
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(randomGeneratedResult));
    QGraphicsScene stubScene;
    EnemyModelType1Test* enemy = new EnemyModelType1Test(
        startPosition,
        generatorStub
    );
    stubScene.addItem(enemy);

    for(int i = 0; i < numberOfMoveFuncExecutions; i++) {
        enemy->move();
    }

    EXPECT_EQ(def::enemy1Level, enemy->getLevel());
    QPointF resultPosition = enemy->getCenterPosition();
    EXPECT_NEAR(
        expectedPosition.x(),
        resultPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedPosition.y(),
        resultPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(expectedDirection, enemy->getDirection());
    delete generatorStub;
}

INSTANTIATE_TEST_SUITE_P(
    MovePath,
    EnemyModelType1MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            0,
            QPointF(0, 0),
            QPointF(
                0,
                def::moveVectorLength
            ),
            def::down
        ),
        std::tr1::make_tuple(
            100,
            0,
            QPointF(0, 0),
            QPointF(
                0,
                def::moveVectorLength * 100
            ),
            def::down
        ),
        std::tr1::make_tuple(
            1,
            1,
            QPointF(0, 0),
            QPointF(
                0.87,
                4.92
            ),
            def::enemy1RightMoveDirection
        ), 
        std::tr1::make_tuple(
            100,
            1,
            QPointF(0, 0),
            QPointF(
                86.82,
                492.40
            ),
            def::enemy1RightMoveDirection
        ),
        std::tr1::make_tuple(
            1,
            1,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                (def::halfSceneWight + 1) - 0.87,
                4.92
            ),
            def::enemy1LeftMoveDirection
        ), 
        std::tr1::make_tuple(
            100,
            1,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                (def::halfSceneWight + 1) - 86.82,
                492.40
            ),
            def::enemy1LeftMoveDirection
        )
    )
);
