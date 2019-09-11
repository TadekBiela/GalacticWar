#include <gtest/gtest.h>
#include "../app/healthview.hpp"

class HealthViewTests : public HealthView
{
public:
    const QProgressBar& getHealthBar() { return m_healthBar; }
};

class HealthViewTestsClass : public testing::Test
{
};

TEST_F(HealthViewTestsClass, UpdateHealthView_UpdateWithValue0_IsZero)
{
    HealthViewTests healthView;

    healthView.updateHealthView(0);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 0);
}

TEST_F(HealthViewTestsClass, UpdateHealthView_UpdateWithValue30_IsEqual)
{
    HealthViewTests healthView;

    healthView.updateHealthView(30);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 30);
}

TEST_F(HealthViewTestsClass, UpdateHealthView_UpdateWithMaxValue_IsEqual)
{
    HealthViewTests healthView;

    healthView.updateHealthView(100);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}

TEST_F(HealthViewTestsClass, UpdateHealthView_UpdateWithMoreThanMaxValueShouldntIncreaseMoreThanMax_IsEqual)
{
    HealthViewTests healthView;

    healthView.updateHealthView(120);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}
