#include <gtest/gtest.h>
#include "../app/healthmodel.hpp"
#include "../app/definitions.hpp"

class HealthModelTest : public HealthModel
{
public:
    HealthModelTest() {}
    virtual ~HealthModelTest() {}

    int getCurrentHealth() const { return m_currentHealth; }
    void setCurrentHealth(int value) { m_currentHealth = value; }
};

class HealthModelTestsClass : public testing::Test
{
};

TEST_F(HealthModelTestsClass, Add_currentHealthIs0Add10Points_ShouldIncreaseHealthTo10)
{
    HealthModelTest model;
    model.setCurrentHealth(0);

    model.add(10);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(10, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Add_currentHealthIs50Add0Points_HealthShouldNotChange)
{
    HealthModelTest model;
    model.setCurrentHealth(50);

    model.add(0);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(50, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Add_currentHealthIsMaxAdd50Points_HealthShouldNotChange)
{
    HealthModelTest model;
    model.setCurrentHealth(def::maxPlayerHealth);

    model.add(50);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(def::maxPlayerHealth, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Add_currentHealthIsMaxMinus10Add50Points_HealthShouldBeMax)
{
    HealthModelTest model;
    model.setCurrentHealth(def::maxPlayerHealth - 10);

    model.add(50);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(def::maxPlayerHealth, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Subtract_currentHealthIsMaxSubtract50Points_HealthShouldBeDecreasedBy50AndStatusShouldBeStillIs)
{
    HealthModelTest model;
    model.setCurrentHealth(def::maxPlayerHealth);

    Health_Status resultStatus = model.subtract(50);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(Health_Status_Still_Is, resultStatus);
    EXPECT_EQ(def::maxPlayerHealth - 50, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Subtract_currentHealthIs10Subtract9Points_HealthShouldBeDecreasedTo1AndStatusShouldBeStillIs)
{
    HealthModelTest model;
    model.setCurrentHealth(10);

    Health_Status resultStatus = model.subtract(9);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(Health_Status_Still_Is, resultStatus);
    EXPECT_EQ(1, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Subtract_currentHealthIs10Subtract10Points_HealthShouldBeDecreasedTo0AndStatusShouldBeNoMore)
{
    HealthModelTest model;
    model.setCurrentHealth(10);

    Health_Status resultStatus = model.subtract(10);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(Health_Status_No_More, resultStatus);
    EXPECT_EQ(0, resultCurrentHealth);
}

TEST_F(HealthModelTestsClass, Subtract_currentHealthIs10Subtract50Points_HealthShouldBeDecreasedTo0AndStatusShouldBeNoMore)
{
    HealthModelTest model;
    model.setCurrentHealth(10);

    Health_Status resultStatus = model.subtract(50);
    int resultCurrentHealth = model.getCurrentHealth();

    EXPECT_EQ(Health_Status_No_More, resultStatus);
    EXPECT_EQ(0, resultCurrentHealth);
}
