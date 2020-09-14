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

    QPointF resultOffset = calculateXYOffset(def::up, def::moveVectorLength);

    EXPECT_EQ(expectedOffset.x(), resultOffset.x());
    EXPECT_EQ(expectedOffset.y(), resultOffset.y());
}

TEST(FunctionsTests, RotatePointBasedOnCenterPoint_RotatedPointIsRightSideOfCenterPointRotate90ToRight_ShouldChangeRotatedPointToDownOfCenterPoint)
{
    QPointF centerPoint(0, 0);
    QPointF rotatedPoint(10, 0);
    QPointF expectedPoint(0, -10);

    rotatePointBasedOnCenterPoint(centerPoint,
                                  90,
                                  rotatedPoint);

    EXPECT_NEAR(expectedPoint.x(), rotatedPoint.x(), 0.01);
    EXPECT_NEAR(expectedPoint.y(), rotatedPoint.y(), 0.01);
}

TEST(FunctionsTests, RotatePointBasedOnCenterPoint_RotatedPointIsRightSideOfCenterPointRotate90ToLeft_ShouldChangeRotatedPointToUpOfCenterPoint)
{
    QPointF centerPoint(0, 0);
    QPointF rotatedPoint(10, 0);
    QPointF expectedPoint(0, 10);

    rotatePointBasedOnCenterPoint(centerPoint,
                                  -90,
                                  rotatedPoint);

    EXPECT_NEAR(expectedPoint.x(), rotatedPoint.x(), 0.01);
    EXPECT_NEAR(expectedPoint.y(), rotatedPoint.y(), 0.01);
}

TEST(FunctionsTests, RotatePointBasedOnCenterPoint_RotatedPointIsUpOnCenterPointRotate90ToLeft_ShouldChangeRotatedPointToLeftSideOfCenterPoint)
{
    QPointF centerPoint(0, 0);
    QPointF rotatedPoint(0, 10);
    QPointF expectedPoint(-10, 0);

    rotatePointBasedOnCenterPoint(centerPoint,
                                  -90,
                                  rotatedPoint);

    EXPECT_NEAR(expectedPoint.x(), rotatedPoint.x(), 0.01);
    EXPECT_NEAR(expectedPoint.y(), rotatedPoint.y(), 0.01);
}

TEST(FunctionsTests, RotatePointBasedOnCenterPoint_RotatedPointIsUpOnCenterPointRotate90ToRight_ShouldChangeRotatedPointToRightSideOfCenterPoint)
{
    QPointF centerPoint(0, 0);
    QPointF rotatedPoint(0, 10);
    QPointF expectedPoint(10, 0);

    rotatePointBasedOnCenterPoint(centerPoint,
                                  90,
                                  rotatedPoint);

    EXPECT_NEAR(expectedPoint.x(), rotatedPoint.x(), 0.01);
    EXPECT_NEAR(expectedPoint.y(), rotatedPoint.y(), 0.01);
}

class FunctionsTestsParamClass : public testing::TestWithParam<std::pair<int, QPointF>>
{
};

TEST_P(FunctionsTestsParamClass, CalculateXYOffset_CheckChangingPositionDependenceOfDirection_IsEqual)
{
    std::pair<int, QPointF> inputParams    = GetParam();
    int                     direction      = inputParams.first;
    QPointF                 expectedOffset = inputParams.second;

    QPointF resultOffset = calculateXYOffset(direction, def::moveVectorLength);

    EXPECT_NEAR(expectedOffset.x(), resultOffset.x(), 0.01);
    EXPECT_NEAR(expectedOffset.y(), resultOffset.y(), 0.01);
}

INSTANTIATE_TEST_SUITE_P(CalculateXYOffset,
                         FunctionsTestsParamClass,
                         testing::Values(std::make_pair(   def::up, QPointF( 0.00l, -5.00l)),   //Direction: up
                                         std::make_pair( def::down, QPointF( 0.00l,  5.00l)),   //Direction: down
                                         std::make_pair( def::left, QPointF(-5.00l,  0.00l)),   //Direction: left
                                         std::make_pair(def::right, QPointF( 5.00l,  0.00l)),   //Direction: right
                                         std::make_pair(        45, QPointF( 3.54l, -3.54l)),   //Direction: up-rigth 45 deg
                                         std::make_pair(       212, QPointF(-2.65l,  4.24l)),   //Direction: down-left 32 deg
                                         std::make_pair(       359, QPointF(-0.09l, -5.00l))    //Direction: up-rigth with 390 deg (should be equal as 30 deg)
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
                                         std::make_pair(QPointF(def::sceneWight + 10,                     9), true),
                                         std::make_pair(QPointF(     def::sceneWight,      def::sceneHeight), false),
                                         std::make_pair(QPointF(                  10, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(                   9, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(def::sceneWight + 10, def::sceneHeight + 10), true),
                                         std::make_pair(QPointF(def::sceneWight +  9, def::sceneHeight +  9), false)
                                        ));
