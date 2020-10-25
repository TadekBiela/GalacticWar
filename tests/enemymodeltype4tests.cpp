#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype4.hpp"
#include "../app/bulletmodel.hpp"
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType4Test : public EnemyModelType4
{
public:
    EnemyModelType4Test(
        QPointF position
    ) :
        EnemyModelType4(
            position
        )
    {}
    virtual ~EnemyModelType4Test() {}

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
    int  getJumpMoveTimeDelay() const {
        return m_jumpMoveTimeDelay;
    }
    bool getIsJumpMove() const {
        return m_isJumpMove;
    }
    enemy_jump_side getJumpSide() const {
        return m_jumpSide;
    }
    void setDirection(int direction) {
        m_direction = direction;
    }
};

class EnemyModelType4TestClass : public testing::Test
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

TEST_F(EnemyModelType4TestClass, Constructor_SpawnPositionIsOnLeftSideOfScene_ShouldSetJumpSideToRight)
{
    EnemyModelType4Test enemyModel(QPointF(2, 7));

    EXPECT_EQ(def::enemy4Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(2, resultPosition.x());
    EXPECT_FLOAT_EQ(7, resultPosition.y());
    EXPECT_EQ(def::enemy4MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy4BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy4MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy4FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(def::enemy4JumpTimeDelay, enemyModel.getJumpMoveTimeDelay());
    EXPECT_FALSE(enemyModel.getIsJumpMove());
    EXPECT_EQ(enemy_jump_side::left, enemyModel.getJumpSide());
}

TEST_F(EnemyModelType4TestClass, Constructor_SpawnPositionIsOnRightSideOfScene_ShouldSetJumpSideToLeft)
{
    EnemyModelType4Test enemyModel(QPointF(def::halfSceneWight + 1, 7));

    EXPECT_EQ(def::enemy4Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(def::halfSceneWight + 1, resultPosition.x());
    EXPECT_FLOAT_EQ(7, resultPosition.y());
    EXPECT_EQ(def::enemy4MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy4BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy4MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy4FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(def::enemy4JumpTimeDelay, enemyModel.getJumpMoveTimeDelay());
    EXPECT_FALSE(enemyModel.getIsJumpMove());
    EXPECT_EQ(enemy_jump_side::right, enemyModel.getJumpSide());
}

TEST_F(EnemyModelType4TestClass, File_ShotOneTime_ShouldAddOneBulletEnemy4ToTheScene)
{
    QPointF expectedEnemyPosition(0, 0);
    QPointF expectedBulletPosition(
        expectedEnemyPosition.x(),
        expectedEnemyPosition.y() + def::enemy4BulletYCoordinateOffsetInPx
    );
    QGraphicsScene mockScene;
    EnemyModelType4Test* enemy = new EnemyModelType4Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType4Test* resultEnemyModel = dynamic_cast<EnemyModelType4Test*>(sceneItems[1]);
    EXPECT_EQ(def::enemy4Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel->getType());
    QPointF resultBulletPosition = resultBulletModel->getCenterPosition();
    EXPECT_NEAR(expectedBulletPosition.x(), resultBulletPosition.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBulletPosition.y(), resultBulletPosition.y(), utdef::floatPrecision);
    EXPECT_EQ(def::enemy4BaseDamage, resultBulletModel->getDamage());
    EXPECT_EQ(def::down, resultBulletModel->rotation());
    delete enemy;
}

typedef std::tr1::tuple<int, QPointF, QPointF> input_params;

class EnemyModelType4MoveParamTestClass : public testing::TestWithParam<input_params>
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

TEST_P(EnemyModelType4MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const QPointF startPosition = std::tr1::get<1>(GetParam());
    const QPointF expectedPosition = std::tr1::get<2>(GetParam());
    QGraphicsScene stubScene;
    EnemyModelType4Test* enemyModel = new EnemyModelType4Test(startPosition);
    stubScene.addItem(enemyModel);

    for(int i = 0; i < numberOfMoveFuncExecutions; i++) {
        enemyModel->move();
    }

    QPointF resultPosition = enemyModel->getCenterPosition();
    EXPECT_NEAR(expectedPosition.x(), resultPosition.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedPosition.y(), resultPosition.y(), utdef::floatPrecision);
    delete enemyModel;
}

INSTANTIATE_TEST_SUITE_P(
    MovePath,
    EnemyModelType4MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            QPointF(0, 0),
            QPointF(0, def::moveVectorLength)
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay - 1,
            QPointF(0, 0),
            QPointF(0, def::moveVectorLength * (def::enemy4JumpTimeDelay - 1))
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay,
            QPointF(0, 0),
            QPointF(
                0,
                def::moveVectorLength * def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay + 1,
            QPointF(0, 0),
            QPointF(
                def::enemy4JumpMoveOffsetInPx,
                (def::moveVectorLength * def::enemy4JumpTimeDelay) + 1
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 2,
            QPointF(0, 0),
            QPointF(
                def::enemy4JumpMoveOffsetInPx * def::enemy4JumpTimeDelay,
                (def::moveVectorLength * def::enemy4JumpTimeDelay) + def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 3,
            QPointF(0, 0),
            QPointF(
                def::enemy4JumpMoveOffsetInPx * def::enemy4JumpTimeDelay,
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 2) + def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 4,
            QPointF(0, 0),
            QPointF(
                0,
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 2) + (def::enemy4JumpTimeDelay * 2)
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 5,
            QPointF(0, 0),
            QPointF(
                0,
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 3) + (def::enemy4JumpTimeDelay * 2)
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::halfSceneWight + 1,
                def::moveVectorLength * def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 2,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                (def::halfSceneWight + 1) - (def::enemy4JumpMoveOffsetInPx * def::enemy4JumpTimeDelay),
                (def::moveVectorLength * def::enemy4JumpTimeDelay) + def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 3,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                (def::halfSceneWight + 1) - (def::enemy4JumpMoveOffsetInPx * def::enemy4JumpTimeDelay),
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 2) + def::enemy4JumpTimeDelay
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 4,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::halfSceneWight + 1,
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 2) + (def::enemy4JumpTimeDelay * 2)
            )
        ),
        std::tr1::make_tuple(
            def::enemy4JumpTimeDelay * 5,
            QPointF(def::halfSceneWight + 1, 0),
            QPointF(
                def::halfSceneWight + 1,
                (def::moveVectorLength * def::enemy4JumpTimeDelay * 3) + (def::enemy4JumpTimeDelay * 2)
            )
        )
    )
);
