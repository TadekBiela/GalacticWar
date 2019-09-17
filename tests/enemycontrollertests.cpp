#include <gtest/gtest.h>
#include "../app/enemycontroller.hpp"

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
