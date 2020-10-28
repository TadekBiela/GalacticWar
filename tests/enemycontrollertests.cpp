#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/enemycontroller.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/definitions.hpp"
#include <QSignalSpy>
#include <QPointF>
#include <QTimer>
#include <QGraphicsScene>
#include <vector>

using namespace testing;

Q_DECLARE_METATYPE(GameObject*)

class EnemyControllerTest : public EnemyController
{
public:
    EnemyControllerTest(GameplayView* view)
        : EnemyController(view){}
    virtual ~EnemyControllerTest() {}
    void setGenerator(IRandomGenerator* generator)
    {
        delete m_generator;
        m_generator = generator;
    }

    int*          getEnemyPercentDistTab() { return m_enemyPercentDistributionTab; }
    const QTimer& getEnemySpawnTimer()     { return m_enemySpawnTimer; }
    int           getRemainigSpawnTime()   { return m_remainigSpawnTime; }
    void          startEnemySpawnTimer()   { m_enemySpawnTimer.start(); }

public slots:
    void spawnEnemy()
    {
        EnemyController::spawnEnemy();
    }
};

class GameplayViewMock : public GameplayView
{
public:
    GameplayViewMock(QWidget* displayWidget)
        : GameplayView(displayWidget) {}
    ~GameplayViewMock() {}

    const QGraphicsScene& getScene() { return m_scene; }
};

class EnemyControllerTestsClass : public testing::Test
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

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfig_ShouldGenerateNewPercentDistributionTab)
{
    EnemyConfiguration inputConfig = { 1000, 2000, 10, 15, 20, 25, 30, 0 };
    std::vector<int> expected = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5
    };
    QWidget displayWidget;
    GameplayView view(&displayWidget);
    EnemyControllerTest enemyController(&view);

    enemyController.changeEnemyConfig(inputConfig);

    std::vector<int> resultEnemyPercDistTab;
    resultEnemyPercDistTab.assign(
        enemyController.getEnemyPercentDistTab(),
        enemyController.getEnemyPercentDistTab() + def::percentDistTabSize
    );
    ASSERT_EQ(expected, resultEnemyPercDistTab);
}

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfigNotContainFirstEnemyType_ShouldGenerateNewPercentDistributionTab)
{
    EnemyConfiguration inputConfig = { 1000, 2000, 0, 15, 20, 25, 30, 10 };
    std::vector<int> expected = {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6
    };
    QWidget displayWidget;
    GameplayView view(&displayWidget);
    EnemyControllerTest enemyController(&view);

    enemyController.changeEnemyConfig(inputConfig);

    std::vector<int> resultEnemyPercDistTab;
    resultEnemyPercDistTab.assign(
        enemyController.getEnemyPercentDistTab(),
        enemyController.getEnemyPercentDistTab() + def::percentDistTabSize
    );
    ASSERT_EQ(expected, resultEnemyPercDistTab);
}

TEST_F(EnemyControllerTestsClass, Destroyed_CheckCorrectWorking_ShouldEmitEnemyDestroyedSignalWithSameParameters)
{
    QWidget             displayWidget;
    GameplayView        view(&displayWidget);
    EnemyControllerTest enemyController(&view);
    QSignalSpy          signalDestroyed(&enemyController, &EnemyControllerTest::enemyDestroyed);
    signalDestroyed.wait(utdef::minSignalTimeDelay);

    enemyController.destroyed(QPointF(40, 130), 4);
    int             resultSignalDestroyedCount = signalDestroyed.count();
    QList<QVariant> resultSignalDestroyed      = signalDestroyed.takeFirst();

    EXPECT_EQ(1,               resultSignalDestroyedCount);
    EXPECT_EQ(QPointF(40,130), resultSignalDestroyed.at(0).toPointF());
    EXPECT_EQ(4,               resultSignalDestroyed.at(1).toInt());
}

TEST_F(EnemyControllerTestsClass, StartSpawning_CheckCorrectWorking_ShouldStartEnemySpawnTimer)
{
    QWidget             displayWidget;
    GameplayView        view(&displayWidget);
    EnemyControllerTest enemyController(&view);
    bool                oldEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();

    enemyController.startSpawning();
    bool resultEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();

    EXPECT_FALSE(oldEnemySpawnTimerStatus);
    EXPECT_TRUE(resultEnemySpawnTimerStatus);
}

TEST_F(EnemyControllerTestsClass, StopSpawning_CheckCorrectWorking_ShouldStopEnemySpawnTimer)
{
    QWidget             displayWidget;
    GameplayView        view(&displayWidget);
    EnemyControllerTest enemyController(&view);
    enemyController.startEnemySpawnTimer(); //manual activation timer
    bool                oldEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();

    enemyController.stopSpawning();
    bool resultEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();

    EXPECT_TRUE(oldEnemySpawnTimerStatus);
    EXPECT_FALSE(resultEnemySpawnTimerStatus);
}


TEST_F(EnemyControllerTestsClass, StopSpawning_GameIsntStart_ShouldSetRemainingTimeOnDefaultValue)
{
    QWidget             displayWidget;
    GameplayView        view(&displayWidget);
    EnemyControllerTest enemyController(&view);
    bool                oldEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();

    enemyController.stopSpawning();
    bool resultEnemySpawnTimerStatus = enemyController.getEnemySpawnTimer().isActive();
    int  resultRemainingSpawnTime    = enemyController.getRemainigSpawnTime();

    EXPECT_FALSE(oldEnemySpawnTimerStatus);
    EXPECT_FALSE(resultEnemySpawnTimerStatus);
    EXPECT_EQ(def::minEnemySpawnTimeDelay, resultRemainingSpawnTime);
}

TEST_F(EnemyControllerTestsClass, SpawnEnemy_CheckIfWillGenerateCorrectEnemyAndEmitSignalToView_IsEqual)
{
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    EXPECT_CALL(*generator, bounded(_,_)).WillOnce(Return(1)).WillOnce(Return(40)).WillOnce(Return(0)).WillOnce(Return(230));
    QWidget              displayWidget;
    GameplayView         view(&displayWidget);
    EnemyControllerTest  enemyController(&view);
    enemyController.setGenerator(generator);
    QSignalSpy signalAdd(&enemyController, &EnemyControllerTest::addEnemyToScene);
    signalAdd.wait(utdef::minSignalTimeDelay);

    enemyController.spawnEnemy();
    int  resultSignalAddCount  = signalAdd.count();
    auto resultEnemy           = qvariant_cast<GameObject*>(signalAdd.takeFirst().at(0));
    int  resultEnemyLevel      = dynamic_cast<EnemyModel*>(resultEnemy)->getLevel();
    auto resultEnemyPosition   = dynamic_cast<EnemyModel*>(resultEnemy)->pos();
    int  resultEnemySpawnDelay = enemyController.getEnemySpawnTimer().interval();

    EXPECT_EQ(1,                          resultSignalAddCount);
    EXPECT_EQ(1,                          resultEnemyLevel);
    EXPECT_EQ(8,                          resultEnemyPosition.x());
    EXPECT_EQ(-def::animationFrameHeight, resultEnemyPosition.y());
    EXPECT_FLOAT_EQ(230, resultEnemySpawnDelay);
    delete resultEnemy;
}

TEST_F(EnemyControllerTestsClass, SpawnEnemy_CheckIfEnemyWillBeAddedToView_IsEqual)
{
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    EXPECT_CALL(*generator, bounded(_,_)).WillOnce(Return(1)).WillOnce(Return(40)).WillOnce(Return(0)).WillOnce(Return(230));
    QWidget              displayWidget;
    GameplayViewMock     view(&displayWidget);
    EnemyControllerTest  enemyController(&view);
    enemyController.setGenerator(generator);

    enemyController.spawnEnemy();
    const QGraphicsScene& resultScene     = view.getScene();
    QList<QGraphicsItem*> resultItemsList = resultScene.items();
    EnemyModel*           resultEnemy     = dynamic_cast<EnemyModel*>(resultItemsList.at(0));

    EXPECT_EQ(1,                          resultItemsList.size());
    EXPECT_EQ(1,                          resultEnemy->getLevel());
    EXPECT_EQ(8,                          resultEnemy->pos().x());
    EXPECT_EQ(-def::animationFrameHeight, resultEnemy->pos().y());
    delete resultEnemy;
}
