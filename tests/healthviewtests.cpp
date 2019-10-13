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

TEST_F(HealthViewTestsClass, Update_UpdateWithValue0_IsZero)
{
    HealthViewTests healthView;

    healthView.update(0);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 0);
}

TEST_F(HealthViewTestsClass, Update_UpdateWithValue30_IsEqual)
{
    HealthViewTests healthView;

    healthView.update(30);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 30);
}

TEST_F(HealthViewTestsClass, Update_UpdateWithMaxValue_IsEqual)
{
    HealthViewTests healthView;

    healthView.update(100);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}

TEST_F(HealthViewTestsClass, Update_UpdateWithMoreThanMaxValueShouldntIncreaseMoreThanMax_IsEqual)
{
    HealthViewTests healthView;

    healthView.update(120);
    const QProgressBar& resultHealthBar = healthView.getHealthBar();

    EXPECT_EQ(resultHealthBar.value(), 100);
}
