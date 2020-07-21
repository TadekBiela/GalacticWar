#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utdefinitions.hpp"
#include "stubs/barviewstub.hpp"
#include "stubs/imagestoragestub.hpp"
#include "stubs/soundstoragestub.hpp"
#include "../app/healthcontroller.hpp"
#include "../app/definitions.hpp"
#include <QSignalSpy>

using namespace testing;

class HealthModelMock : public HealthModel
{
public:
    HealthModelMock() {}
    virtual ~HealthModelMock() {}

    MOCK_METHOD(Health_Status, subtract, (int), ());
};

class HealthControllerTest : public HealthController
{
public:
    HealthControllerTest(QWidget*         displayWidget,
                         HealthModelMock* modelMock,
                         BarViewStub*     viewMock)
        : HealthController(displayWidget)
    {
        m_model = modelMock;
        m_view  = viewMock;
    }
    virtual ~HealthControllerTest()
    {
        m_model = nullptr;
        m_view  = nullptr;
    }
};

class HealthControllerTestsClass : public testing::Test
{
public:
    void SetUp()
    {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown()
    {
        delete g_imageStorage;
    }
};

TEST_F(HealthControllerTestsClass, SubtractHealthPoints_currentHealthIsMaxSubtract10Points_ShouldNotSendSignalNoHealth)
{
    QWidget              displayWidget;
    HealthModelMock      modelMock;
    BarViewStub          viewMock(&displayWidget);
    HealthControllerTest controller(&displayWidget, &modelMock, &viewMock);
    ON_CALL(modelMock, subtract(_)).WillByDefault(Return(Health_Status_Still_Is));
    QSignalSpy signalNoHealth(&controller, &HealthControllerTest::noHealth);
    signalNoHealth.wait(utdef::minSignalTimeDelay);

    controller.subtractHealthPoints(10);
    int resultSignalNoHealth = signalNoHealth.count();

    EXPECT_EQ(0, resultSignalNoHealth);
}

TEST_F(HealthControllerTestsClass, SubtractHealthPoints_currentHealthIsMaxSubtractMaxPoints_ShouldSendSignalNoHealth)
{
    QWidget              displayWidget;
    HealthModelMock      modelMock;
    BarViewStub          viewMock(&displayWidget);
    HealthControllerTest controller(&displayWidget, &modelMock, &viewMock);
    ON_CALL(modelMock, subtract(def::maxPlayerHealth)).WillByDefault(Return(Health_Status_No_More));
    QSignalSpy signalNoHealth(&controller, &HealthControllerTest::noHealth);
    signalNoHealth.wait(utdef::minSignalTimeDelay);

    controller.subtractHealthPoints(def::maxPlayerHealth);
    int resultSignalNoHealth = signalNoHealth.count();

    EXPECT_EQ(1, resultSignalNoHealth);
}
