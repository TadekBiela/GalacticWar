#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemymodeltype5.hpp"
#include "../app/bulletmodel.hpp"
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyModelType5Test : public EnemyModelType5
{
public:
    EnemyModelType5Test(
        QPointF position
    ) :
        EnemyModelType5(
            position
        )
    {}
    virtual ~EnemyModelType5Test() {}

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
    enemy_weapon getWeaponMode() const {
        return m_weaponMode;
    }
    int getChangeMoveSideTimeDelay() const {
        return m_changeMoveSideTimeDelay;
    }
    enemy_move_side getMoveSide() const {
        return m_moveSide;
    }
};

class EnemyModelType5TestClass : public testing::Test
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

TEST_F(EnemyModelType5TestClass, Constructor_SpawnPositionIsOnLeftSideOfScene_ShouldStartOfLeftSideAndSetMoveSideToRight)
{
    EnemyModelType5Test enemyModel(QPointF(2, 7));

    EXPECT_EQ(def::enemy5Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(def::enemy5StartXCoordinate, resultPosition.x());
    EXPECT_FLOAT_EQ(def::enemy5StartYCoordinate, resultPosition.y());
    EXPECT_EQ(def::enemy5MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy5BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy5MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy5FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(enemy_weapon::mode_small, enemyModel.getWeaponMode());
    EXPECT_EQ(def::enemy5ChangeMoveSideTimeDelay, enemyModel.getChangeMoveSideTimeDelay());
    EXPECT_EQ(enemy_move_side::right, enemyModel.getMoveSide());
}

TEST_F(EnemyModelType5TestClass, Constructor_SpawnPositionIsOnRightSideOfScene_ShouldStartOfRightSideAndSetMoveSideToLeft)
{
    EnemyModelType5Test enemyModel(QPointF(def::halfSceneWidth + 1, 7));

    EXPECT_EQ(def::enemy5Level, enemyModel.getLevel());
    QPointF resultPosition = enemyModel.getCenterPosition();
    EXPECT_FLOAT_EQ(def::sceneWidth - def::enemy5StartXCoordinate, resultPosition.x());
    EXPECT_FLOAT_EQ(def::enemy5StartYCoordinate, resultPosition.y());
    EXPECT_EQ(def::enemy5MaxHealthPoints, enemyModel.getHealth());
    EXPECT_EQ(def::enemy5BaseDamage, enemyModel.getDamage());
    EXPECT_EQ(def::down, enemyModel.getDirection());
    EXPECT_EQ(0, enemyModel.getAnimationFrameXIdx());
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy5MoveTimeDelay, resultMoveTimer.interval());
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(def::enemy5FireTimeDelay, resultFireTimer.interval());
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(def::animationFrameDuration, resultAnimTimer.interval());
    EXPECT_EQ(enemy_weapon::mode_small, enemyModel.getWeaponMode());
    EXPECT_EQ(def::enemy5ChangeMoveSideTimeDelay, enemyModel.getChangeMoveSideTimeDelay());
    EXPECT_EQ(enemy_move_side::left, enemyModel.getMoveSide());
}

TEST_F(EnemyModelType5TestClass, File_ShotOneTime_ShouldAddTwoBulletOfSmallWeapon)
{
    QPointF expectedEnemyPosition(
        def::enemy5StartXCoordinate,
        def::enemy5StartYCoordinate
    );
    QPointF expectedBulletLeftPosition(
        expectedEnemyPosition.x() - def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedBulletRightPosition(
        expectedEnemyPosition.x() + def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QGraphicsScene mockScene;
    EnemyModelType5Test* enemy = new EnemyModelType5Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType5Test* resultEnemyModel = dynamic_cast<EnemyModelType5Test*>(sceneItems[2]);
    EXPECT_EQ(def::enemy5Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultBulletLeftModel = dynamic_cast<BulletModel*>(sceneItems[1]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletLeftModel->getType());
    QPointF resultBulletLeftPosition = resultBulletLeftModel->getCenterPosition();
    EXPECT_NEAR(
        expectedBulletLeftPosition.x(),
        resultBulletLeftPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedBulletLeftPosition.y(),
        resultBulletLeftPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultBulletLeftModel->getDamage());
    EXPECT_EQ(def::down, resultBulletLeftModel->rotation());
    BulletModel* resultBulletRightModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletRightModel->getType());
    QPointF resultBulletRightPosition = resultBulletRightModel->getCenterPosition();
    EXPECT_NEAR(
        expectedBulletRightPosition.x(),
        resultBulletRightPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedBulletRightPosition.y(),
        resultBulletRightPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultBulletRightModel->getDamage());
    EXPECT_EQ(def::down, resultBulletRightModel->rotation());
    delete enemy;
}

TEST_F(EnemyModelType5TestClass, File_ShotTwoTimes_ShouldAddTwoBulletOfSmallWeaponAndTwoBulletOfMediumWeapon)
{
    QPointF expectedEnemyPosition(
        def::enemy5StartXCoordinate,
        def::enemy5StartYCoordinate
    );
    QPointF expectedSmallBulletLeftPosition(
        expectedEnemyPosition.x() - def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedSmallBulletRightPosition(
        expectedEnemyPosition.x() + def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedMediumBulletLeftPosition(
        expectedEnemyPosition.x() - def::enemy5MediumWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedMediumBulletRightPosition(
        expectedEnemyPosition.x() + def::enemy5MediumWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QGraphicsScene mockScene;
    EnemyModelType5Test* enemy = new EnemyModelType5Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();
    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType5Test* resultEnemyModel = dynamic_cast<EnemyModelType5Test*>(sceneItems[4]);
    EXPECT_EQ(def::enemy5Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultSmallBulletLeftModel = dynamic_cast<BulletModel*>(sceneItems[3]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultSmallBulletLeftModel->getType());
    QPointF resultSmallBulletLeftPosition = resultSmallBulletLeftModel->getCenterPosition();
    EXPECT_NEAR(
        expectedSmallBulletLeftPosition.x(),
        resultSmallBulletLeftPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedSmallBulletLeftPosition.y(),
        resultSmallBulletLeftPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultSmallBulletLeftModel->getDamage());
    EXPECT_EQ(def::down, resultSmallBulletLeftModel->rotation());
    BulletModel* resultSmallBulletRightModel = dynamic_cast<BulletModel*>(sceneItems[2]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultSmallBulletRightModel->getType());
    QPointF resultSmallBulletRightPosition = resultSmallBulletRightModel->getCenterPosition();
    EXPECT_NEAR(
        expectedSmallBulletRightPosition.x(),
        resultSmallBulletRightPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedSmallBulletRightPosition.y(),
        resultSmallBulletRightPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultSmallBulletRightModel->getDamage());
    EXPECT_EQ(def::down, resultSmallBulletRightModel->rotation());
    BulletModel* resultMediumBulletLeftModel = dynamic_cast<BulletModel*>(sceneItems[1]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultMediumBulletLeftModel->getType());
    QPointF resultMediumBulletLeftPosition = resultMediumBulletLeftModel->getCenterPosition();
    EXPECT_NEAR(
        expectedMediumBulletLeftPosition.x(),
        resultMediumBulletLeftPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedMediumBulletLeftPosition.y(),
        resultMediumBulletLeftPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5MediumWeaponDamage, resultMediumBulletLeftModel->getDamage());
    EXPECT_EQ(def::down, resultMediumBulletLeftModel->rotation());
    BulletModel* resultMediumBulletRightModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultMediumBulletRightModel->getType());
    QPointF resultMediumBulletRightPosition = resultMediumBulletRightModel->getCenterPosition();
    EXPECT_NEAR(
        expectedMediumBulletRightPosition.x(),
        resultMediumBulletRightPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedMediumBulletRightPosition.y(),
        resultMediumBulletRightPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5MediumWeaponDamage, resultMediumBulletRightModel->getDamage());
    EXPECT_EQ(def::down, resultMediumBulletRightModel->rotation());
    delete enemy;
}

TEST_F(EnemyModelType5TestClass, File_ThreeTwoTimes_ShouldAddTwoBulletOfSmallWeaponTwoBulletOfMediumWeaponAndOneBigWeapon)
{
    QPointF expectedEnemyPosition(
        def::enemy5StartXCoordinate,
        def::enemy5StartYCoordinate
    );
    QPointF expectedSmallBulletLeftPosition(
        expectedEnemyPosition.x() - def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedSmallBulletRightPosition(
        expectedEnemyPosition.x() + def::enemy5SmallWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedMediumBulletLeftPosition(
        expectedEnemyPosition.x() - def::enemy5MediumWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedMediumBulletRightPosition(
        expectedEnemyPosition.x() + def::enemy5MediumWeaponXOffset,
        expectedEnemyPosition.y()
    );
    QPointF expectedBigBulletPosition(
        expectedEnemyPosition.x(),
        expectedEnemyPosition.y() + def::enemy5BigWeaponYOffset
    );
    QGraphicsScene mockScene;
    EnemyModelType5Test* enemy = new EnemyModelType5Test(QPointF(0, 0));
    mockScene.addItem(enemy);

    enemy->fire();
    enemy->fire();
    enemy->fire();

    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType5Test* resultEnemyModel = dynamic_cast<EnemyModelType5Test*>(sceneItems[5]);
    EXPECT_EQ(def::enemy5Level, resultEnemyModel->getLevel());
    QPointF resultEnemyPosition = resultEnemyModel->getCenterPosition();
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyPosition.x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyPosition.y());
    BulletModel* resultSmallBulletLeftModel = dynamic_cast<BulletModel*>(sceneItems[4]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultSmallBulletLeftModel->getType());
    QPointF resultSmallBulletLeftPosition = resultSmallBulletLeftModel->getCenterPosition();
    EXPECT_NEAR(
        expectedSmallBulletLeftPosition.x(),
        resultSmallBulletLeftPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedSmallBulletLeftPosition.y(),
        resultSmallBulletLeftPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultSmallBulletLeftModel->getDamage());
    EXPECT_EQ(def::down, resultSmallBulletLeftModel->rotation());
    BulletModel* resultSmallBulletRightModel = dynamic_cast<BulletModel*>(sceneItems[3]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultSmallBulletRightModel->getType());
    QPointF resultSmallBulletRightPosition = resultSmallBulletRightModel->getCenterPosition();
    EXPECT_NEAR(
        expectedSmallBulletRightPosition.x(),
        resultSmallBulletRightPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedSmallBulletRightPosition.y(),
        resultSmallBulletRightPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5SmallWeaponDamage, resultSmallBulletRightModel->getDamage());
    EXPECT_EQ(def::down, resultSmallBulletRightModel->rotation());
    BulletModel* resultMediumBulletLeftModel = dynamic_cast<BulletModel*>(sceneItems[2]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultMediumBulletLeftModel->getType());
    QPointF resultMediumBulletLeftPosition = resultMediumBulletLeftModel->getCenterPosition();
    EXPECT_NEAR(
        expectedMediumBulletLeftPosition.x(),
        resultMediumBulletLeftPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedMediumBulletLeftPosition.y(),
        resultMediumBulletLeftPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5MediumWeaponDamage, resultMediumBulletLeftModel->getDamage());
    EXPECT_EQ(def::down, resultMediumBulletLeftModel->rotation());
    BulletModel* resultMediumBulletRightModel = dynamic_cast<BulletModel*>(sceneItems[1]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultMediumBulletRightModel->getType());
    QPointF resultMediumBulletRightPosition = resultMediumBulletRightModel->getCenterPosition();
    EXPECT_NEAR(
        expectedMediumBulletRightPosition.x(),
        resultMediumBulletRightPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedMediumBulletRightPosition.y(),
        resultMediumBulletRightPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5MediumWeaponDamage, resultMediumBulletRightModel->getDamage());
    EXPECT_EQ(def::down, resultMediumBulletRightModel->rotation());
    BulletModel* resultBigBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);
    EXPECT_EQ(game_object_type::enemy_bullet, resultBigBulletModel->getType());
    QPointF resultBigBulletPosition = resultBigBulletModel->getCenterPosition();
    EXPECT_NEAR(
        expectedBigBulletPosition.x(),
        resultBigBulletPosition.x(),
        utdef::floatPrecision
    );
    EXPECT_NEAR(
        expectedBigBulletPosition.y(),
        resultBigBulletPosition.y(),
        utdef::floatPrecision
    );
    EXPECT_EQ(def::enemy5BigWeaponDamage, resultBigBulletModel->getDamage());
    EXPECT_EQ(def::down, resultBigBulletModel->rotation());
    delete enemy;
}

typedef std::tr1::tuple<int, QPointF, QPointF> input_params;

class EnemyModelType5MoveParamTestClass : public testing::TestWithParam<input_params>
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

TEST_P(EnemyModelType5MoveParamTestClass, Move_CheckCorrectCalculatingOfMovePath_ShouldMoveToExpectedPoint)
{
    const int numberOfMoveFuncExecutions = std::tr1::get<0>(GetParam());
    const QPointF startPosition = std::tr1::get<1>(GetParam());
    const QPointF expectedPosition = std::tr1::get<2>(GetParam());
    QGraphicsScene stubScene;
    EnemyModelType5Test* enemyModel = new EnemyModelType5Test(startPosition);
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
    EnemyModelType5MoveParamTestClass,
    testing::Values(
        std::tr1::make_tuple(
            1,
            QPointF(0, 0),
            QPointF(
                def::enemy5StartXCoordinate + def::enemy5XCoordinateOffsetInPx,
                def::enemy5StartYCoordinate + def::enemy5YCoordinateOffsetInPx
            )
        ),
        std::tr1::make_tuple(
            def::enemy5ChangeMoveSideTimeDelay,
            QPointF(0, 0),
            QPointF(
                def::enemy5StartXCoordinate + (def::enemy5XCoordinateOffsetInPx * def::enemy5ChangeMoveSideTimeDelay),
                def::enemy5StartYCoordinate + (def::enemy5YCoordinateOffsetInPx * def::enemy5ChangeMoveSideTimeDelay)
            )
        ),
        std::tr1::make_tuple(
            def::enemy5ChangeMoveSideTimeDelay + 1,
            QPointF(0, 0),
            QPointF(
                def::enemy5StartXCoordinate + (def::enemy5XCoordinateOffsetInPx * (def::enemy5ChangeMoveSideTimeDelay - 1)),
                def::enemy5StartYCoordinate + (def::enemy5YCoordinateOffsetInPx * (def::enemy5ChangeMoveSideTimeDelay + 1))
            )
        ),
        std::tr1::make_tuple(
            def::enemy5ChangeMoveSideTimeDelay * 2,
            QPointF(0, 0),
            QPointF(
                def::enemy5StartXCoordinate,
                def::enemy5StartYCoordinate + (def::enemy5YCoordinateOffsetInPx * def::enemy5ChangeMoveSideTimeDelay * 2)
            )
        ),
        std::tr1::make_tuple(
            def::enemy5ChangeMoveSideTimeDelay * 2 + 1,
            QPointF(0, 0),
            QPointF(
                def::enemy5StartXCoordinate + def::enemy5XCoordinateOffsetInPx,
                def::enemy5StartYCoordinate + ((def::enemy5YCoordinateOffsetInPx * def::enemy5ChangeMoveSideTimeDelay * 2) + def::enemy5YCoordinateOffsetInPx) 
            )
        )
    )
);
