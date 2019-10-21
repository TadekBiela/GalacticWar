#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/enemycontroller.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/definitions.hpp"
#include <QSignalSpy>
#include <QPointF>
#include <QTimer>
#include <QGraphicsScene>
#include <vector>

class EnemyControllerTest : public EnemyController
{
public:
    EnemyControllerTest(GeneralView*      view,
                        IRandomGenerator* generator)
                         : EnemyController(view,
                                           generator){}
    virtual ~EnemyControllerTest() {}

    int*          getEnemyPercentDistTab() { return m_enemyPercentDistributionTab; }
    const QTimer& getEnemySpawnTimer()     { return m_enemySpawnTimer; }

public slots:
    void spawnEnemyTest() { EnemyController::spawnEnemy(); }
};

class GeneralViewMock : public GeneralView
{
public:
    GeneralViewMock() {}
    ~GeneralViewMock() {}

    const QGraphicsScene& getScene() { return m_scene; }
};

class EnemyControllerTestsClass : public testing::Test
{
};

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfigShouldGenerateNewPercentDistributionTab_IsEqual)
{
    EnemyConfiguration inputConfig = { 10, 15, 20, 25, 30, 0 };
    std::vector<int>   expected    =
                       { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                         2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
                         3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                         3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    RandomGeneratorStub* generator   = new RandomGeneratorStub();
    GeneralView*         view        = new GeneralView;
    EnemyControllerTest  enemyController(view, generator);

    enemyController.changeEnemyConfiguration(inputConfig);
    std::vector<int> resultEnemyPercDistTab;
    resultEnemyPercDistTab.assign(enemyController.getEnemyPercentDistTab(),
                                  enemyController.getEnemyPercentDistTab() + def::percentDistTabSize);

    ASSERT_EQ(resultEnemyPercDistTab, expected);
    delete view;
    delete generator;
}

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfigNotContainFirstEnemyTypeShouldGenerateNewPercentDistributionTab_IsEqual)
{
    EnemyConfiguration inputConfig = { 0, 15, 20, 25, 30, 10 };
    std::vector<int>   expected    =
                       { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                         2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
                         3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                         3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                         6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
    RandomGeneratorStub* generator   = new RandomGeneratorStub();
    GeneralView*         view        = new GeneralView;
    EnemyControllerTest  enemyController(view, generator);

    enemyController.changeEnemyConfiguration(inputConfig);
    std::vector<int> resultEnemyPercDistTab;
    resultEnemyPercDistTab.assign(enemyController.getEnemyPercentDistTab(),
                                  enemyController.getEnemyPercentDistTab() + def::percentDistTabSize);

    ASSERT_EQ(resultEnemyPercDistTab, expected);
    delete view;
    delete generator;
}

TEST_F(EnemyControllerTestsClass, Destroyed_ShouldEmitEnemyDestroyedSignalWithSameParameters_IsEqual)
{
    RandomGeneratorStub* generator = new RandomGeneratorStub();
    GeneralView*         view      = new GeneralView;
    EnemyControllerTest  enemyController(view, generator);
    QSignalSpy           signalDestroyed(&enemyController, &EnemyControllerTest::enemyDestroyed);
    signalDestroyed.wait(utdef::minSignalTimeDelay);

    enemyController.destroyed(QPointF(40, 130), 4);
    int             resultSignalDestroyedCount = signalDestroyed.count();
    QList<QVariant> resultSignalDestroyed      = signalDestroyed.takeFirst();

    EXPECT_EQ(resultSignalDestroyedCount,             1);
    EXPECT_EQ(resultSignalDestroyed.at(0).toPointF(), QPointF(40,130));
    EXPECT_EQ(resultSignalDestroyed.at(1).toInt(),    4);
    delete view;
    delete generator;
}

TEST_F(EnemyControllerTestsClass, SpawnEnemy_CheckIfWillGenerateCorrectEnemyAndEmitSignalToView_IsEqual)
{
    int sequance[4] = { 1, 40, 0, 230 };
    RandomSequanceGeneratorStub* generator = new RandomSequanceGeneratorStub(4, sequance);
    GeneralView* view = new GeneralView;
    EnemyControllerTest enemyController(view, generator);
    QSignalSpy signalAdd(&enemyController, &EnemyControllerTest::addEnemyToScene);
    signalAdd.wait(utdef::minSignalTimeDelay);

    enemyController.spawnEnemyTest();
    int  resultSignalAddCount  = signalAdd.count();
    auto resultEnemy           = qvariant_cast<QGraphicsItem*>(signalAdd.takeFirst().at(0));
    int  resultEnemyLevel      = dynamic_cast<EnemyModel*>(resultEnemy)->getLevel();
    auto resultEnemyPosition   = dynamic_cast<EnemyModel*>(resultEnemy)->pos();
    int  resultEnemySpawnDelay = enemyController.getEnemySpawnTimer().interval();

    EXPECT_EQ(resultSignalAddCount,    1);
    EXPECT_EQ(resultEnemyLevel,        1);
    EXPECT_EQ(resultEnemyPosition.x(), 40);
    EXPECT_EQ(resultEnemyPosition.y(), -def::animationFrameHeight);
    EXPECT_NEAR(resultEnemySpawnDelay, 230, 2);
    delete resultEnemy;
    delete generator;
    delete view;
}

TEST_F(EnemyControllerTestsClass, SpawnEnemy_CheckIfEnemyWillBeAddedToView_IsEqual)
{
    int sequance[4] = { 1, 40, 0, 230 };
    RandomSequanceGeneratorStub* generator = new RandomSequanceGeneratorStub(4, sequance);
    GeneralViewMock* view = new GeneralViewMock;
    EnemyControllerTest enemyController(dynamic_cast<GeneralView*>(view), generator);

    enemyController.spawnEnemyTest();
    const QGraphicsScene& resultScene     = view->getScene();
    QList<QGraphicsItem*> resultItemsList = resultScene.items();
    EnemyModel*           resultEnemy     = dynamic_cast<EnemyModel*>(resultItemsList.at(0));

    EXPECT_EQ(resultItemsList.size(),  1);
    EXPECT_EQ(resultEnemy->getLevel(), 1);
    EXPECT_EQ(resultEnemy->pos().x(),  40);
    EXPECT_EQ(resultEnemy->pos().y(),  -def::animationFrameHeight);
    delete resultEnemy;
    delete generator;
    delete view;
}
