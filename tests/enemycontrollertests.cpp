#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "../app/enemycontroller.hpp"
#include <QSignalSpy>
#include <QPointF>

class EnemyControllerTest : public EnemyController
{
public:
    explicit EnemyControllerTest(GeneralView* view) :
                                 EnemyController(view){}

    EnemyConfiguration getCurrConfig()     { return m_currentConfiguration; }
    const QTimer&      getEnemySpawTiemr() { return m_enemySpawnTimer; }
};

class EnemyControllerTestsClass : public testing::Test
{
};

TEST_F(EnemyControllerTestsClass, ChangeEnemyConfiguration_NewConfigShouldReplaceCurrent_IsEqual)
{
    EnemyConfiguration  inputConfig = { 10, 15, 20, 25, 30, 0 };
    GeneralView*        view = new GeneralView;
    EnemyControllerTest enemyController(view);

    enemyController.changeEnemyConfiguration(inputConfig);
    EnemyConfiguration resultCurrConfig = enemyController.getCurrConfig();

    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType1, 10);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType2, 15);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType3, 20);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType4, 25);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType5, 30);
    EXPECT_EQ(resultCurrConfig.proportionOfEnemyType6,  0);
}

TEST_F(EnemyControllerTestsClass, Destroyed_ShouldEmitEnemyDestroyedSignalWithSameParameters_IsEqual)
{
    GeneralView*        view = new GeneralView;
    EnemyControllerTest enemyController(view);
    QSignalSpy          signalDestroyed(&enemyController, &EnemyControllerTest::enemyDestroyed);
    signalDestroyed.wait(utdef::minSignalTimeDelay);

    enemyController.destroyed(QPointF(40, 130), 4);
    int             resultSignalDestroyedCount = signalDestroyed.count();
    QList<QVariant> resultSignalDestroyed      = signalDestroyed.takeFirst();

    EXPECT_EQ(resultSignalDestroyedCount,             1);
    EXPECT_EQ(resultSignalDestroyed.at(0).toPointF(), QPointF(40,130));
    EXPECT_EQ(resultSignalDestroyed.at(1).toInt(),    4);
}
