#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/bulletmodel.hpp"
#include "../app/enemyturret.hpp"
#include "../app/enemymodeltype6.hpp"
#include <QGraphicsScene>
#include <tr1/tuple>

class EnemyTurretTest : public EnemyTurret
{
public:
    EnemyTurretTest(
        QGraphicsItem* parent,
        enemy_turret_type type,
        QPointF position,
        int damage,
        int fireTimeDelay,
        int startRotationDegree,
        enemy_turret_rotate_direction rotationDirection,
        int rotateTimeDelay
    ) :
        EnemyTurret(
            parent,
            type,
            position,
            damage,
            fireTimeDelay,
            startRotationDegree,
            rotationDirection,
            rotateTimeDelay
        )
    {}
    virtual ~EnemyTurretTest() {}

    void fire() { EnemyTurret::fire(); }
    void rotate() { EnemyTurret::rotate(); }

    int getDamage() const {
        return m_damage;
    }
    fireEnemyTurret getFireTurretFuncPtr() const {
        return fireTurret;
    }
    const QTimer& getFireTimer() const {
        return m_fireTimer;
    }
    enemy_turret_rotate_direction getRotationDirection() const {
        return  m_rotationDirection;
    }
    int getRotationDegree() const {
        return m_rotationDegree;
    }
    int getMaxRotationDegree() const {
        return m_maxRotationDegree;
    }
    const QTimer& getRotateTimer() const{
        return m_rotateTimer;
    }
};

class EnemyParentTest : public QObject, public QGraphicsPixmapItem
{
public:
    EnemyParentTest(QPointF startPosition) {
        setPos(startPosition);
    }
    virtual ~EnemyParentTest() {}
};

class EnemyTurretTestsClass : public testing::Test
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(36, 36);
        g_soundStorage = new SoundStorageStub;
        m_parentItem = new EnemyParentTest(QPointF(0, 0));
        m_scene = new QGraphicsScene;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
        delete m_parentItem;
        delete m_scene;
    }

    EnemyParentTest* m_parentItem;
    QGraphicsScene* m_scene;
};

TEST_F(EnemyTurretTestsClass, Constructor_CreateDoubleCannonsTurret_ShouldCreateTurretWithDoubleCannons)
{
    const QPoint expectPosition(0, 0);
    const int expectedDamage = 10;
    const int expectedFireTimeDelay = 100;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int expectedRotationDegree = 0;
    const int expectedMaxRotationDegree = expectedRotationDegree + 90;
    const int expectedRotateTimeDelay = 100;

    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::double_cannons,
        expectPosition,
        expectedDamage,
        expectedFireTimeDelay,
        expectedRotationDegree,
        expectedTurretRotateDirection,
        expectedRotateTimeDelay
    );

    EXPECT_EQ(game_object_type::enemy_turret, turret.getType());
    EXPECT_EQ(m_parentItem, turret.parentItem());
    EXPECT_EQ(expectPosition, turret.getCenterPosition());
    EXPECT_EQ(expectedDamage, turret.getDamage());
    EXPECT_EQ(&doubleCannonTurretFireFunc, turret.getFireTurretFuncPtr());
    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
    const QTimer& resultFireTimer = turret.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(expectedFireTimeDelay, resultFireTimer.interval());
    const QTimer& resultRotateTimer = turret.getRotateTimer();
    EXPECT_FALSE(resultRotateTimer.isActive());
    EXPECT_FLOAT_EQ(expectedRotateTimeDelay, resultRotateTimer.interval());
}

TEST_F(EnemyTurretTestsClass, Constructor_CreateTripleCannonsTurret_ShouldCreateTurretWithTripleCannons)
{
    const QPoint expectPosition(0, 0);
    const int expectedDamage = 10;
    const int expectedFireTimeDelay = 100;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int expectedRotationDegree = 0;
    const int expectedMaxRotationDegree = expectedRotationDegree + 90;
    const int expectedRotateTimeDelay = 100;

    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        expectPosition,
        expectedDamage,
        expectedFireTimeDelay,
        expectedRotationDegree,
        expectedTurretRotateDirection,
        expectedRotateTimeDelay
    );

    EXPECT_EQ(game_object_type::enemy_turret, turret.getType());
    EXPECT_EQ(m_parentItem, turret.parentItem());
    EXPECT_EQ(expectPosition, turret.getCenterPosition());
    EXPECT_EQ(expectedDamage, turret.getDamage());
    EXPECT_EQ(&tripleCannonTurretFireFunc, turret.getFireTurretFuncPtr());
    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
    const QTimer& resultFireTimer = turret.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(expectedFireTimeDelay, resultFireTimer.interval());
    const QTimer& resultRotateTimer = turret.getRotateTimer();
    EXPECT_FALSE(resultRotateTimer.isActive());
    EXPECT_FLOAT_EQ(expectedRotateTimeDelay, resultRotateTimer.interval());
}

TEST_F(EnemyTurretTestsClass, Start_DefaultAfterCreateAllTimersArNotActive_ShouldActivateAllTimers)
{
    const int expectedFireTimeDelay = 100;
    const int expectedRotateTimeDelay = 100;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        expectedFireTimeDelay,
        0,
        enemy_turret_rotate_direction::right,
        expectedRotateTimeDelay
    );

    turret.start();

    const QTimer& resultFireTimer = turret.getFireTimer();
    EXPECT_TRUE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(expectedFireTimeDelay, resultFireTimer.interval());
    const QTimer& resultRotateTimer = turret.getRotateTimer();
    EXPECT_TRUE(resultRotateTimer.isActive());
    EXPECT_FLOAT_EQ(expectedRotateTimeDelay, resultRotateTimer.interval());
}

TEST_F(EnemyTurretTestsClass, Stop_StartTimersAfterCreate_ShouldDeactivateAllTimers)
{
    const int expectedFireTimeDelay = 100;
    const int expectedRotateTimeDelay = 100;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        expectedFireTimeDelay,
        0,
        enemy_turret_rotate_direction::right,
        expectedRotateTimeDelay
    );
    turret.start();

    turret.stop();

    const QTimer& resultFireTimer = turret.getFireTimer();
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FLOAT_EQ(expectedFireTimeDelay, resultFireTimer.interval());
    const QTimer& resultRotateTimer = turret.getRotateTimer();
    EXPECT_FALSE(resultRotateTimer.isActive());
    EXPECT_FLOAT_EQ(expectedRotateTimeDelay, resultRotateTimer.interval());
}

TEST_F(EnemyTurretTestsClass, Rotate_OnceRotateToRight_ShouldIncreaseStartDegreeBy1)
{
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = 1;
    const int expectedMaxRotationDegree = startRotationDegree + 90;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        expectedTurretRotateDirection,
        100
    );

    turret.rotate();

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToRightAlmostToMax_ShouldIncreaseStartDegreeBy89AndStillRotateDirectionToLeft)
{
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = 89;
    const int expectedMaxRotationDegree = startRotationDegree + 90;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        expectedTurretRotateDirection,
        100
    );
    const int numOfRotations = 89;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToRightToMax_ShouldIncreaseStartDegreeBy90ChangeRotateDirectionToRightAndMaxShouldBeSameAsStartDegree)
{
    const enemy_turret_rotate_direction startTurretRotateDirection = enemy_turret_rotate_direction::right;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::left;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = 90;
    const int expectedMaxRotationDegree = startRotationDegree;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        startTurretRotateDirection,
        100
    );
    const int numOfRotations = 90;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToRightToMaxPlus1_ShouldIncreaseStartDegreeBy89ChangeRotateDirectionToLeftAndMaxShouldBeSameAsStartDegree)
{
    const enemy_turret_rotate_direction startTurretRotateDirection = enemy_turret_rotate_direction::right;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::left;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = 89;
    const int expectedMaxRotationDegree = startRotationDegree;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        startTurretRotateDirection,
        100
    );
    const int numOfRotations = 91;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_OnceRotateToLeft_ShouldDecreaseStartDegreeBy1)
{
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::left;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = -1;
    const int expectedMaxRotationDegree = startRotationDegree - 90;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        expectedTurretRotateDirection,
        100
    );

    turret.rotate();

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToLeftAlmostToMax_ShouldDecreaseStartDegreeBy89AndStillRotateDirectionToLeft)
{
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::left;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = -89;
    const int expectedMaxRotationDegree = startRotationDegree - 90;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        expectedTurretRotateDirection,
        100
    );
    const int numOfRotations = 89;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToLeftToMax_ShouldDecreaseStartDegreeBy90ChangeRotateDirectionToRightAndMaxShouldBeSameAsStartDegree)
{
    const enemy_turret_rotate_direction startTurretRotateDirection = enemy_turret_rotate_direction::left;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = -90;
    const int expectedMaxRotationDegree = startRotationDegree;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        startTurretRotateDirection,
        100
    );
    const int numOfRotations = 90;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

TEST_F(EnemyTurretTestsClass, Rotate_RotateToLeftToMaxPlus1_ShouldDecreaseStartDegreeBy89ChangeRotateDirectionToRightAndMaxShouldBeSameAsStartDegree)
{
    const enemy_turret_rotate_direction startTurretRotateDirection = enemy_turret_rotate_direction::left;
    const enemy_turret_rotate_direction expectedTurretRotateDirection = enemy_turret_rotate_direction::right;
    const int startRotationDegree = 0;
    const int expectedRotationDegree = -89;
    const int expectedMaxRotationDegree = startRotationDegree;
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::triple_cannons,
        QPointF(0,0),
        10,
        100,
        startRotationDegree,
        startTurretRotateDirection,
        100
    );
    const int numOfRotations = 91;

    for(int rotationIdx = 0; rotationIdx < numOfRotations; rotationIdx++) {
        turret.rotate();
    }

    EXPECT_EQ(expectedTurretRotateDirection, turret.getRotationDirection());
    EXPECT_EQ(expectedRotationDegree, turret.getRotationDegree());
    EXPECT_EQ(expectedMaxRotationDegree, turret.getMaxRotationDegree());
}

typedef std::tr1::tuple<int, int, float, float, float, float> input_params;

class EnemyTurretFireTestsParamClass : public testing::TestWithParam<input_params>
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
        dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(36, 36);
        g_soundStorage = new SoundStorageStub;
        m_parentItem = new EnemyParentTest(QPointF(0, 0));
        m_scene = new QGraphicsScene;
    }
    void TearDown() {
        delete g_imageStorage;
        delete g_soundStorage;
        delete m_parentItem;
        delete m_scene;
    }

    EnemyParentTest* m_parentItem;
    QGraphicsScene* m_scene;
};

TEST_P(EnemyTurretFireTestsParamClass, Fire_TurretIsRotatedTo135DegreeAndParentIsRotated180Degree_ShouldCreateTwoBullesWith270DegreeMoveDirections)
{
    const int turretRotation = std::tr1::get<0>(GetParam());
    const int parentRotation = std::tr1::get<1>(GetParam());
    const int expectedBulletDirection = turretRotation + parentRotation;
    const float expectedBullet1XCorrdinateOffset = std::tr1::get<2>(GetParam());
    const float expectedBullet1YCorrdinateOffset = std::tr1::get<3>(GetParam());
    const float expectedBullet2XCorrdinateOffset = std::tr1::get<4>(GetParam());
    const float expectedBullet2YCorrdinateOffset = std::tr1::get<5>(GetParam());
    EnemyTurretTest turret(
        m_parentItem,
        enemy_turret_type::double_cannons,
        QPoint(0, 0),
        10,
        100,
        turretRotation,
        enemy_turret_rotate_direction::right,
        100
    );
    m_scene->addItem(m_parentItem);
    m_parentItem->setRotation(parentRotation);
    QPointF expectedBullet1Position(
        turret.scenePos().x() + expectedBullet1XCorrdinateOffset,
        turret.scenePos().y() + expectedBullet1YCorrdinateOffset
    );
    QPointF expectedBullet2Position(
        turret.scenePos().x() + expectedBullet2XCorrdinateOffset,
        turret.scenePos().y() + expectedBullet2YCorrdinateOffset
    );

    turret.fire();

    auto resultSceneItems = m_scene->items();
    EXPECT_EQ(4, resultSceneItems.size());
    BulletModel* resultBullet1 = dynamic_cast<BulletModel*>(resultSceneItems.at(0));
    EXPECT_NEAR(expectedBullet1Position.x(), resultBullet1->getCenterPosition().x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBullet1Position.y(), resultBullet1->getCenterPosition().y(), utdef::floatPrecision);
    EXPECT_EQ(expectedBulletDirection, resultBullet1->rotation());
    BulletModel* resultBullet2 = dynamic_cast<BulletModel*>(resultSceneItems.at(1));
    EXPECT_NEAR(expectedBullet2Position.x(), resultBullet2->getCenterPosition().x(), utdef::floatPrecision);
    EXPECT_NEAR(expectedBullet2Position.y(), resultBullet2->getCenterPosition().y(), utdef::floatPrecision);
    EXPECT_EQ(expectedBulletDirection, resultBullet2->rotation());
}

INSTANTIATE_TEST_SUITE_P(
    Fire,
    EnemyTurretFireTestsParamClass,
    testing::Values(
            std::tr1::make_tuple(0, 0, 25, 0, 11, 0),
            std::tr1::make_tuple(90, 0, 0, 25, 0, 11),
            std::tr1::make_tuple(45, 45, 0, 25, 0, 11),
            std::tr1::make_tuple(90, def::down, 0, -25, 0, -11),
            std::tr1::make_tuple(135, def::down, 17.68, -17.68, 7.78, -7.78)
    )
);
