#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/definitions.hpp"
#include "../app/enemymodeltype6.hpp"
#include "../app/bulletmodel.hpp"
#include <QSignalSpy>
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType6Test : public EnemyModelType6
{
public:
    EnemyModelType6Test(
        QPointF position,
        IRandomGenerator* generator
    ) :
        EnemyModelType6(
            position,
            generator
        )
    {}
    virtual ~EnemyModelType6Test() {}

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
    EnemyTurret* getFrontTurretPtr() const {
        return m_frontTurret;
    }
    void move() {
        EnemyModelType6::move();
    }
};

class EnemyModelType6TestClass : public testing::Test
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

TEST_F(EnemyModelType6TestClass, EnemyModelType6Constructor_StartPositionIsOnLeftSideOfScene_ShouldCreateModelBehindSceneLeftBorder)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationDegrees,
            def::enemy6MaxRotationDegrees
        )
    ).WillByDefault(Return(def::enemy6MinRotationDegrees));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinStartYCoordinate,
            def::enemy6MaxStartYCoordinate
        )
    ).WillByDefault(Return(def::enemy6MinStartYCoordinate));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationTimeDelay,
            def::enemy6MaxRotationTimeDelay
        )
    ).WillByDefault(Return(def::enemy6MinRotationTimeDelay));

    EnemyModelType6Test enemyModel(
        QPointF(2, 7),
        generatorStub
    );

    int resultLevel = enemyModel.getLevel();
    EXPECT_EQ(def::enemy6Level, resultLevel);
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(-112, resultPosition.x());
    EXPECT_FLOAT_EQ(def::enemy6MinStartYCoordinate, resultPosition.y());
    int resultHealth = enemyModel.getHealth();
    EXPECT_EQ(def::enemy6MaxHealthPoints, resultHealth);
    int resultDamage = enemyModel.getDamage();
    EXPECT_EQ(def::enemy6BaseDamage, resultDamage);
    int resultDirection = enemyModel.getDirection();
    EXPECT_EQ(115, resultDirection);
    int resultAnimationFrameXIdx = enemyModel.getAnimationFrameXIdx();
    EXPECT_EQ(0, resultAnimationFrameXIdx);
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy6MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy6FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType6TestClass, EnemyModelType6Constructor_StartPositionIsOnRightSideOfScene_ShouldCreateModelBehindSceneRightBorder)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationDegrees,
            def::enemy6MaxRotationDegrees
        )
    ).WillByDefault(Return(def::enemy6MinRotationDegrees));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinStartYCoordinate,
            def::enemy6MaxStartYCoordinate
            )
    ).WillByDefault(Return(def::enemy6MinStartYCoordinate));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationTimeDelay,
            def::enemy6MaxRotationTimeDelay
        )
    ).WillByDefault(Return(def::enemy6MinRotationTimeDelay));

    EnemyModelType6Test enemyModel(
        QPointF(def::sceneWidth - 1, 7),
        generatorStub
    );

    int resultLevel = enemyModel.getLevel();
    EXPECT_EQ(def::enemy6Level, resultLevel);
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ((def::sceneWidth + 112), resultPosition.x());
    EXPECT_FLOAT_EQ(def::enemy6MinStartYCoordinate, resultPosition.y());
    int resultHealth = enemyModel.getHealth();
    EXPECT_EQ(def::enemy6MaxHealthPoints, resultHealth);
    int resultDamage = enemyModel.getDamage();
    EXPECT_EQ(def::enemy6BaseDamage, resultDamage);
    int resultDirection = enemyModel.getDirection();
    EXPECT_EQ(245, resultDirection);
    int resultAnimationFrameXIdx = enemyModel.getAnimationFrameXIdx();
    EXPECT_EQ(0, resultAnimationFrameXIdx);
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy6MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy6FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    delete generatorStub;
}

TEST_F(EnemyModelType6TestClass, Start_DefaultAllTimerAsDeactivated_ShouldActivateAllTimers)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));
    EnemyModelType6Test enemyModel(QPointF(0, 0), generatorStub);

    enemyModel.start();

    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_TRUE(resultMoveTimer.isActive());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_TRUE(resultFireTimer.isActive());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_TRUE(resultAnimTimer.isActive());
    delete generatorStub;
}

TEST_F(EnemyModelType6TestClass, Stop_AllTimersAreActivated_ShouldDeactivateAllTimers)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));
    EnemyModelType6Test enemyModel(QPointF(0, 0), generatorStub);
    enemyModel.start();

    enemyModel.stop();

    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    delete generatorStub;
}

typedef std::tr1::tuple<int, int, int, int, QPointF, QPointF, int> input_params;

class EnemyModelType6MoveParamTestClass : public testing::TestWithParam<input_params>
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(64, 256);
        g_soundStorage = new SoundStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
    }
};

TEST_P(EnemyModelType6MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const int maneuverDegrees = std::tr1::get<1>(GetParam());
    const int startYCoorinate = std::tr1::get<2>(GetParam());
    const int rotationManeuverTimeDelay = std::tr1::get<3>(GetParam());
    const QPointF startPositionFromEnemyController = std::tr1::get<4>(GetParam());
    const QPointF expectedPosition = std::tr1::get<5>(GetParam());
    const int expectedDirection = std::tr1::get<6>(GetParam());
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationDegrees,
            def::enemy6MaxRotationDegrees
        )
    ).WillByDefault(Return(maneuverDegrees));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinStartYCoordinate,
            def::enemy6MaxStartYCoordinate
            )
    ).WillByDefault(Return(startYCoorinate));
    ON_CALL(
        *generatorStub,
        bounded(
            def::enemy6MinRotationTimeDelay,
            def::enemy6MaxRotationTimeDelay
        )
    ).WillByDefault(Return(rotationManeuverTimeDelay));
    QGraphicsScene stubScene;
    EnemyModelType6Test* enemyModel = new EnemyModelType6Test(startPositionFromEnemyController, generatorStub);
    stubScene.addItem(enemyModel);

    for(int i = 0; i < numberOfMoveFuncExecutions; i++) {
        enemyModel->move();
    }

    QPointF resultPosition = enemyModel->getCenterPosition();
    EXPECT_NEAR(expectedPosition.x(), resultPosition.x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedPosition.y(), resultPosition.y(), utdef::floatPrecision);
    EXPECT_EQ(expectedDirection, enemyModel->getDirection());
    delete enemyModel;
    delete generatorStub;
}

INSTANTIATE_TEST_SUITE_P(
    StartPositionOnLeftSideOfScene,
    EnemyModelType6MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(
                (-def::enemy6StartXCoordinateOffset + 1.81),
                (def::enemy6MinStartYCoordinate + 0.85)
            ),
            115
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay - 1,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(339.34, 162.46),
            115
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(341.15, 163.31),
            116
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay + 1,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(342.95, 164.19),
            117
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay + def::enemy6MinRotationDegrees,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(406.41, 267.74),
            def::down
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay + def::enemy6MinRotationDegrees + 1,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(406.41, 269.74),
            def::down
        ),
        std::tr1::make_tuple(
            def::enemy6MinRotationTimeDelay + def::enemy6MinRotationDegrees + 100,
            def::enemy6MinRotationDegrees,
            def::enemy6MinStartYCoordinate,
            def::enemy6MinRotationTimeDelay,
            QPointF(0, 0),
            QPointF(406.41, 467.74),
            def::down
        )
    )
);

INSTANTIATE_TEST_SUITE_P(
    StartPositionOnRightSideOfScene,
    EnemyModelType6MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(710.03, 68.35),
            260
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay - 1,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(142.78, 168.37),
            260
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(140.81, 168.72),
            259
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay + 1,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(138.85, 169.10),
            258
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay + def::enemy6MaxRotationDegrees,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(47.11, 282.39),
            def::down
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay + def::enemy6MaxRotationDegrees + 1,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(47.11, 284.39),
            def::down
        ),
        std::tr1::make_tuple(
            def::enemy6MaxRotationTimeDelay + def::enemy6MaxRotationDegrees + 100,
            def::enemy6MaxRotationDegrees,
            def::enemy6MaxStartYCoordinate,
            def::enemy6MaxRotationTimeDelay,
            QPointF((def::halfSceneWidth + 1), 0),
            QPointF(47.11, 482.39),
            def::down
        )
    )
);
