#include <gtest/gtest.h>
#include "../app/definitions.hpp"
#include "../app/functions.hpp"

TEST(FunctionsTests, ChangeBoolToMinusOneOrOne_TrueOnInput_ShouldReturnOne)
{
    int result = changeBoolToMinusOneOrOne(true);

    EXPECT_EQ(1, result);
}

TEST(FunctionsTests, ChangeBoolToMinusOneOrOne_FalseOnInput_ShouldReturnMinusOne)
{
    int result = changeBoolToMinusOneOrOne(false);

    EXPECT_EQ(-1, result);
}

TEST(FunctionsTests, CalculateXYOffset_UpDirection_ShouldReturnPositionX0Yminus10)
{
    QPointF expectedOffset(0, -def::moveVectorLength);

    QPointF resultOffset = calculateXYOffset(def::up);

    EXPECT_EQ(expectedOffset.x(), resultOffset.x());
    EXPECT_EQ(expectedOffset.y(), resultOffset.y());
}

class FunctionsTestsParamClass : public testing::TestWithParam<std::pair<int, QPointF>>
{
};

TEST_P(FunctionsTestsParamClass, Move_CheckChangingPositionDependenceOfDirection_IsEqual)
{
    std::pair<int, QPointF> inputParams    = GetParam();
    int                     direction      = inputParams.first;
    QPointF                 expectedOffset = inputParams.second;

    QPointF resultOffset = calculateXYOffset(direction);

    EXPECT_NEAR(expectedOffset.x(), resultOffset.x(), 0.01);
    EXPECT_NEAR(expectedOffset.y(), resultOffset.y(), 0.01);
}

INSTANTIATE_TEST_SUITE_P(Move,
                         FunctionsTestsParamClass,
                         testing::Values(std::make_pair(   def::up, QPointF(  0.00l, -10.00l)),   //Direction: up
                                         std::make_pair( def::down, QPointF(  0.00l,  10.00l)),   //Direction: down
                                         std::make_pair( def::left, QPointF(-10.00l,   0.00l)),   //Direction: left
                                         std::make_pair(def::right, QPointF( 10.00l,   0.00l)),   //Direction: right
                                         std::make_pair(        45, QPointF(  7.07l,  -7.07l)),   //Direction: up-rigth 45 deg
                                         std::make_pair(       212, QPointF( -5.30l,   8.48l)),   //Direction: down-left 32 deg
                                         std::make_pair(       359, QPointF( -0.17l, -10.00l))    //Direction: up-rigth with 390 deg (should be equal as 30 deg)
                                        ));

class FunctionsOutOfSceneTestsParamClass : public testing::TestWithParam<std::pair<QPointF, bool>>
{
};

TEST_P(FunctionsOutOfSceneTestsParamClass, IsOutOfScene_CheckingIfObjectIsInScene_ShouldReturnTrueIfObjectIsStillOnScene)
{
    std::pair<QPointF, bool> inputParams    = GetParam();
    QPointF                  objectPosition = inputParams.first;
    bool                     expected       = inputParams.second;
    QPixmap                  objectPixmap(10, 10);

    bool result = isOutOfScene(objectPosition, objectPixmap);

    EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(OutOfScene,
                         FunctionsOutOfSceneTestsParamClass,
                         testing::Values(std::make_pair(QPointF(                   0,                     0), false),
                                         std::make_pair(QPointF(                 -10,                   -10), true),
                                         std::make_pair(QPointF(                  -9,                    -9), false),
                                         std::make_pair(QPointF(                 -10,                    20), true),
                                         std::make_pair(QPointF(                  20,                   -10), true),
                                         std::make_pair(QPointF(def::sceneWight + 10,                    10), true),
                                         std::make_pair(QPointF(def::sceneWight + 10,                    9),  true),
                                         std::make_pair(QPointF(     def::sceneWight,      def::sceneHeight), false),
                                         std::make_pair(QPointF(                  10, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(                   9, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(def::sceneWight + 10, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(def::sceneWight +  9, def::sceneHeight +  9), false)
                                        ));
