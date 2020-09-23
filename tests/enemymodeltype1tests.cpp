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
    EnemyModelType1Test(QPointF position,
                        IRandomGenerator* generator)
        : EnemyModelType1(position,
                          generator){}
    virtual ~EnemyModelType1Test() {}

    int getLevel() const { return m_level; }
    QPointF getPosition() const { return pos(); }
    int getHealth() const { return m_health; }
    int getDamage() const { return m_damage; }
    int getDirection() const { return m_direction; }
    int getAnimationFrameXIdx() const { return m_animationFrameXIdx; }
    const QTimer& getFireTimer() const { return m_fireTimer; }
    const QTimer& getMoveTimer() const { return m_moveTimer; }
    const QTimer& getAnimationTimer() const { return m_animationTimer; }
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
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));

    EnemyModelType1Test enemyModel(QPointF(2, 7), generatorStub);
    int resultLevel = enemyModel.getLevel();
    QPointF resultPosition = enemyModel.getCenterPosition();
    int resultHealth = enemyModel.getHealth();
    int resultDamage = enemyModel.getDamage();
    int resultDirection = enemyModel.getDirection();
    int resultAnimationFrameXIdx = enemyModel.getAnimationFrameXIdx();
    const QTimer& resultMoveTimer = enemyModel.getMoveTimer();
    const QTimer& resultFireTimer = enemyModel.getFireTimer();
    const QTimer& resultAnimTimer = enemyModel.getAnimationTimer();

    EXPECT_EQ(1, resultLevel);
    EXPECT_EQ(30, resultHealth);
    EXPECT_EQ(10, resultDamage);
    EXPECT_EQ(def::down, resultDirection);
    EXPECT_EQ(0, resultAnimationFrameXIdx);
    EXPECT_FALSE(resultMoveTimer.isActive());
    EXPECT_FALSE(resultFireTimer.isActive());
    EXPECT_FALSE(resultAnimTimer.isActive());
    EXPECT_FLOAT_EQ(40, resultMoveTimer.interval());
    EXPECT_FLOAT_EQ(1000, resultFireTimer.interval());
    EXPECT_FLOAT_EQ(100, resultAnimTimer.interval());
    EXPECT_FLOAT_EQ(2, resultPosition.x());
    EXPECT_FLOAT_EQ(7, resultPosition.y());
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsRightSideOfSceneDirectionCalculationShouldBe180_IsEqual)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));

    EnemyModelType1Test enemyModel(QPointF(450, 0), generatorStub);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(180, resultDirection);
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsRightSideOfSceneDirectionCalculationShouldBe190_IsEqual)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));

    EnemyModelType1Test enemyModel(QPointF(450, 0), generatorStub);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(190, resultDirection);
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsLeftSideOfSceneDirectionCalculationShouldBe180_IsEqual)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));

    EnemyModelType1Test enemyModel(QPointF(250, 0), generatorStub);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(180, resultDirection);
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, EnemyModelType1Constructor_PositionIsLeftSideOfSceneDirectionCalculationShouldBe170_IsEqual)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(1));

    EnemyModelType1Test enemyModel(QPointF(250, 0), generatorStub);
    int resultDirection = enemyModel.getDirection();

    EXPECT_EQ(170, resultDirection);
    delete generatorStub;
}

TEST_F(EnemyModelType1TestClass, Fire_CheckIfBulletIsAddedToScene_IsEqual)
{
    NiceMock<RandomGeneratorStub>* generatorStub = new NiceMock<RandomGeneratorStub>;
    ON_CALL(*generatorStub, bounded(_, _)).WillByDefault(Return(0));
    QGraphicsScene mockScene;
    QPointF expectedEnemyPosition(100, 100);
    EnemyModelType1Test* enemyModel = new EnemyModelType1Test(expectedEnemyPosition, generatorStub);
    QPointF expectedBulletPosition(expectedEnemyPosition.x(), (expectedEnemyPosition.y() + 28));
    mockScene.addItem(enemyModel);
    //Change bullet pixmap size
    dynamic_cast<ImageStorageStub*>(g_imageStorage)->setDummyImageSize(3, 15);

    enemyModel->fire();
    QList<QGraphicsItem*> sceneItems = mockScene.items();
    EnemyModelType1Test* resultEnemyModel = dynamic_cast<EnemyModelType1Test*>(sceneItems[1]);
    BulletModel* resultBulletModel = dynamic_cast<BulletModel*>(sceneItems[0]);

    EXPECT_EQ(1, resultEnemyModel->getLevel());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.x(), resultEnemyModel->getCenterPosition().x());
    EXPECT_FLOAT_EQ(expectedEnemyPosition.y(), resultEnemyModel->getCenterPosition().y());
    EXPECT_EQ(game_object_type::enemy_bullet, resultBulletModel->getType());
    EXPECT_FLOAT_EQ(expectedBulletPosition.x(), resultBulletModel->getCenterPosition().x());
    EXPECT_FLOAT_EQ(expectedBulletPosition.y(), resultBulletModel->getCenterPosition().y());
    EXPECT_EQ(10, resultBulletModel->getDamage());
    delete enemyModel;
    delete generatorStub;
}
