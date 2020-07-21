#include <gtest/gtest.h>
#include "utdefinitions.hpp"
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
};

class ControlPlaneTestsClass : public testing::Test
{
};

TEST_F(ControlPlaneTestsClass, MousePressEvent_MouseLeftButtonPressed_ShouldSendSignalMousePressed)
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

    EXPECT_EQ(1, resultSignalMousePressed);
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_MouseRightButtonPressed_ShouldNotSendSignalMousePressed)
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

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_MouseLeftButtonReleased_ShouldSendSignalMouseReleased)
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

    EXPECT_EQ(1, resultSignalMouseReleased);
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_MouseRightButtonReleased_ShouldNotSendSignalMouseReleased)
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

TEST_F(ControlPlaneTestsClass, KeyPressEvent_KeyEscPressed_ShouldSendSignalEscKeyPressed)
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

    EXPECT_EQ(1, resultSignalEscKeyPressed);
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_KeyAPressed_ShouldNotSendSignalEscKeyPressed)
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
