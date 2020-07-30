#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "stubs/imagestoragestub.hpp"
#include  "../app/controlplane.hpp"
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QSignalSpy>

using namespace testing;

class ControlPlaneTest : public ControlPlane
{
public:
    ControlPlaneTest(QWidget* displayWidget)
        : ControlPlane(displayWidget){}
    virtual ~ControlPlaneTest() {}
    void setState(controller_state state) { m_state = state; }
};

class ControlPlaneTestsClass : public testing::Test
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

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedMouseRightButtonPressed_ShouldNotSendSignalMousePressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonPress,
                      QPointF(0,0),
                      Qt::MouseButton::RightButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    QSignalSpy signalMousePressed(&controller, &ControlPlaneTest::mousePressed);
    signalMousePressed.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);
    int resultSignalMousePressed = signalMousePressed.count();

    EXPECT_EQ(0, resultSignalMousePressed);
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedMouseLeftButtonPressed_ShouldNotSendSignalMousePressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonPress,
                      QPointF(0,0),
                      Qt::MouseButton::LeftButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    QSignalSpy signalMousePressed(&controller, &ControlPlaneTest::mousePressed);
    signalMousePressed.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);
    int resultSignalMousePressed = signalMousePressed.count();

    EXPECT_EQ(0, resultSignalMousePressed);
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_ActivatedMouseRightButtonPressed_ShouldNotSendSignalMousePressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonPress,
                      QPointF(0,0),
                      Qt::MouseButton::RightButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    controller.setState(controller_state::activated);
    QSignalSpy signalMousePressed(&controller, &ControlPlaneTest::mousePressed);
    signalMousePressed.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);
    int resultSignalMousePressed = signalMousePressed.count();

    EXPECT_EQ(0, resultSignalMousePressed);
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedMouseRightButtonReleased_ShouldNotSendSignalMouseReleased)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonRelease,
                      QPointF(0,0),
                      Qt::MouseButton::RightButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    QSignalSpy signalMouseReleased(&controller, &ControlPlaneTest::mouseReleased);
    signalMouseReleased.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);
    int resultSignalMouseReleased = signalMouseReleased.count();

    EXPECT_EQ(0, resultSignalMouseReleased);
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedMouseLeftButtonReleased_ShouldNotSendSignalMouseReleased)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonRelease,
                      QPointF(0,0),
                      Qt::MouseButton::LeftButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    QSignalSpy signalMouseReleased(&controller, &ControlPlaneTest::mouseReleased);
    signalMouseReleased.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);
    int resultSignalMouseReleased = signalMouseReleased.count();

    EXPECT_EQ(0, resultSignalMouseReleased);
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedMouseRightButtonReleased_ShouldNotSendSignalMouseReleased)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonRelease,
                      QPointF(0,0),
                      Qt::MouseButton::RightButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    controller.setState(controller_state::activated);
    QSignalSpy signalMouseReleased(&controller, &ControlPlaneTest::mouseReleased);
    signalMouseReleased.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);
    int resultSignalMouseReleased = signalMouseReleased.count();

    EXPECT_EQ(0, resultSignalMouseReleased);
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedMouseLeftButtonReleased_ShouldSendSignalMouseReleased)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QMouseEvent event(QEvent::MouseButtonRelease,
                      QPointF(0,0),
                      Qt::MouseButton::LeftButton,
                      Qt::NoButton,
                      Qt::NoModifier);
    controller.setState(controller_state::activated);
    QSignalSpy signalMouseReleased(&controller, &ControlPlaneTest::mouseReleased);
    signalMouseReleased.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);
    int resultSignalMouseReleased = signalMouseReleased.count();

    EXPECT_EQ(1, resultSignalMouseReleased);
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_DeactivatedKeyEscPressed_ShouldNotSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_Escape,
                    Qt::NoModifier);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTest::escKeyPressed);
    signalEscKeyPressed.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);
    int resultSignalEscKeyPressed = signalEscKeyPressed.count();

    EXPECT_EQ(0, resultSignalEscKeyPressed);
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_ActivatedKeyEscPressed_ShouldSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_Escape,
                    Qt::NoModifier);
    controller.setState(controller_state::activated);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTest::escKeyPressed);
    signalEscKeyPressed.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);
    int resultSignalEscKeyPressed = signalEscKeyPressed.count();

    EXPECT_EQ(1, resultSignalEscKeyPressed);
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_DeactivatedKeyAPressed_ShouldNotSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_A,
                    Qt::NoModifier);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTest::escKeyPressed);
    signalEscKeyPressed.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);
    int resultSignalEscKeyPressed = signalEscKeyPressed.count();

    EXPECT_EQ(0, resultSignalEscKeyPressed);
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_ActivatedKeyAPressed_ShouldNotSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_A,
                    Qt::NoModifier);
    controller.setState(controller_state::activated);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTest::escKeyPressed);
    signalEscKeyPressed.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);
    int resultSignalEscKeyPressed = signalEscKeyPressed.count();

    EXPECT_EQ(0, resultSignalEscKeyPressed);
}
