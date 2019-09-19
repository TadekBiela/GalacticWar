#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/randomgeneratorstub.hpp"
#include "../app/enemycontroller.hpp"
#include "../app/enemymodeltype1.hpp"
#include "../app/definitions.hpp"
#include <QSignalSpy>
#include <QPointF>

class EnemyControllerTest : public EnemyController
{
public:
    explicit EnemyControllerTest(GeneralView* view,
                                 IRandomGenerator* generator) :
                                 EnemyController(view,
                                                 generator){}

    EnemyConfiguration getCurrConfig()     { return m_currentConfiguration; }
    const QTimer&      getEnemySpawTiemr() { return m_enemySpawnTimer; }

public slots:
    void spawnEnemyTest() { EnemyController::spawnEnemy(); }
};

class EnemyControllerTestsClass : public testing::Test
{
};

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfigShouldReplaceCurrent_IsEqual)
{
    EnemyConfiguration   inputConfig = { 10, 15, 20, 25, 30, 0 };
    RandomGeneratorStub* generator   = new RandomGeneratorStub();
    GeneralView*         view        = new GeneralView;
    EnemyControllerTest  enemyController(view, generator);

    enemyController.changeEnemyConfiguration(inputConfig);
    EnemyConfiguration resultCurrConfig = enemyController.getCurrConfig();

    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType1, 10);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType2, 15);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType3, 20);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType4, 25);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType5, 30);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType6,  0);
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
    int sequance[2] = { 1, 40 };
    RandomSequanceGeneratorStub* generator = new RandomSequanceGeneratorStub(2, sequance);
    GeneralView* view = new GeneralView;
    EnemyControllerTest enemyController(view, generator);
    QSignalSpy signalAdd(&enemyController, &EnemyControllerTest::addEnemyToScene);
    signalAdd.wait(utdef::minSignalTimeDelay);

    enemyController.spawnEnemyTest();
    int  resultSignalAddCount = signalAdd.count();
    auto resultEnemy          = signalAdd.takeFirst().at(0).value<QGraphicsItem*>();
    int  resultEnemyLevel     = dynamic_cast<EnemyModel*>(resultEnemy)->getLevel();
    auto resultEnemyPosition  = dynamic_cast<EnemyModel*>(resultEnemy)->pos();

    EXPECT_EQ(resultSignalAddCount,    1);
    EXPECT_EQ(resultEnemyLevel,        1);
    EXPECT_EQ(resultEnemyPosition.x(), 40);
    EXPECT_EQ(resultEnemyPosition.y(), -def::animationFrameHeight);
    delete view;
    delete generator;
    delete resultEnemy;
}
