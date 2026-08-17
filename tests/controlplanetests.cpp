#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "utdefinitions.hpp"
#include "mocks/cursorcontrollermock.hpp"
#include "stubs/imagestoragestub.hpp"
#include "../app/controlplane.hpp"
#include "../app/definitions.hpp"
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QSignalSpy>
#include <tr1/tuple>

using namespace testing;

class ControlPlaneTestable : public ControlPlane
{
public:
    using ControlPlane::ControlPlane;

    auto getMovePosition() const -> const QPointF&
    {
        return m_movePosition;
    }

    controller_state getState() const {
        return m_state;
    }
    control_mode getControlMode() const {
        return m_controlMode;
    }
    bool getKeyMoveUpPressed() const {
        return m_keyMoveUpPressed;
    }
    bool getKeyMoveDownPressed() const {
        return m_keyMoveDownPressed;
    }
    bool getKeyMoveLeftPressed() const {
        return m_keyMoveLeftPressed;
    }
    bool getKeyMoveRightPressed() const {
        return m_keyMoveRightPressed;
    }
    void setState(controller_state state) {
        m_state = state;
    }
    void setControlMode(control_mode mode) {
        m_controlMode = mode;
    }
    void setKeyMoveUpPressed(bool keyMoveUpPressed) {
        m_keyMoveUpPressed = keyMoveUpPressed;
    }
    void setKeyMoveDownPressed(bool keyMoveDownPressed) {
        m_keyMoveDownPressed = keyMoveDownPressed;
    }
    void setKeyMoveLeftPressed(bool keyMoveLeftPressed) {
        m_keyMoveLeftPressed = keyMoveLeftPressed;
    }
    void setKeyMoveRightPressed(bool keyMoveRightPressed) {
        m_keyMoveRightPressed = keyMoveRightPressed;
    }
};

class ControlPlaneTests : public Test
{
public:
    void SetUp() override {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown() override {
        delete g_imageStorage;
    }

    static auto getMouseEvent(const QPointF& position) -> QMouseEvent
    {
        return QMouseEvent(
            QEvent::MouseMove,
            position,
            Qt::NoButton,
            Qt::NoButton,
            Qt::NoModifier
        );
    };

protected:
    QWidget displayWidget{};
    std::unique_ptr<CursorControllerMock> cursorControllerMock{ std::make_unique<CursorControllerMock>() };
};

TEST_F(ControlPlaneTests, Constructor_CreateNewObject_ShouldSetControlToMouseAndDeactivate)
{
    ControlPlaneTestable controller(&displayWidget);

    EXPECT_EQ(controller_state::deactivated, controller.getState());
    EXPECT_EQ(control_mode::mouse, controller.getControlMode());
}

TEST_F(ControlPlaneTests, MousePressEvent_DeactivatedControlKeyboardModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_DeactivatedControlMouseModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_DeactivatedControlKeyboardModeLeftButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_DeactivatedControlMouseModeLeftButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_ActivatedControlKeyboardModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_ActivatedControlMouseModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MousePressEvent_ActivatedControlMouseModeLeftButtonPressed_ShouldSendStartFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTestable::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(1, startFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_DeactivatedControlKeyboardModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_DeactivatedControlMouseModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_DeactivatedControlKeyboardModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_DeactivatedControlMouseModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_ActivatedControlKeyboardModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_ActivatedControlMouseModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_ActivatedControlKeyboardModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTests, MouseReleaseEvent_ActivatedControlMouseModeLeftButtonReleased_ShouldSendStopFireSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTestable::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(1, stopFireSignal.count());
}

inline auto PrintTo(const QPointF& point, std::ostream* os) -> void
{
    const QString typeStr = QString("x = %1, y = %2").arg(point.x()).arg(point.y());
    *os << typeStr.toStdString();
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorNearTheCenterOfDisplay_ShouldNotChangeCursorPosition)
{
    const QPointF expectedMousePos{ def::halfSceneWidth + 2, def::halfSceneHeight - 1 };
    QMouseEvent event{ getMouseEvent(expectedMousePos) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(0);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&event);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_Cursor15PxFromTopEdgeAndHorizontallyCentered_ShouldNotChangeCursorPosition)
{
    const QPointF expectedMousePos{ def::halfSceneWidth, 15 };
    QMouseEvent event{ getMouseEvent(expectedMousePos) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(0);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&event);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromTopEdgeAndHorizontallyCentered_ShouldChangeCursorPositionTo15PxFromTopEdge)
{
    const QPointF expectedMousePos{ def::halfSceneWidth, 15 };
    QMouseEvent mouseMoveEventBelowMinY{ getMouseEvent({ def::halfSceneWidth, 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventBelowMinY);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromBottomEdgeAndHorizontallyCentered_ShouldChangeCursorPositionTo15PxFromBottomEdge)
{
    const QPointF expectedMousePos{ def::halfSceneWidth, def::sceneHeight - 15 };
    QMouseEvent mouseMoveEventAboveMaxY{ getMouseEvent({ def::halfSceneWidth, def::sceneHeight - 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventAboveMaxY);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromLeftEdgeAndVerticallyCentered_ShouldChangeCursorPositionTo15PxFromLeftEdge)
{
    const QPointF expectedMousePos{ 15, def::halfSceneHeight };
    QMouseEvent mouseMoveEventLeft{ getMouseEvent({ 14, def::halfSceneHeight }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventLeft);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromRightEdgeAndVerticallyCentered_ShouldChangeCursorPositionTo15PxFromRightEdge)
{
    const QPointF expectedMousePos{ def::sceneWidth - 15, def::halfSceneHeight };
    QMouseEvent mouseMoveEventRight{ getMouseEvent({ def::sceneWidth - 14, def::halfSceneHeight }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventRight);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromTopAndLeftEdges_ShouldChangeCursorPositionTo15PxFromTopAndLeftEdges)
{
    const QPointF expectedMousePos{ 15, 15 };
    QMouseEvent mouseMoveEventTopLeft{ getMouseEvent({ 14, 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventTopLeft);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorLessThan15PxFromTopAndMoreThanRightEdge_ShouldChangeCursorPositionTo15PxFromTopAndRightEdges)
{
    const QPointF expectedMousePos{ def::sceneWidth - 15, 15 };
    QMouseEvent mouseMoveEventTopRight{ getMouseEvent({ def::sceneWidth - 14, 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventTopRight);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorMoreThan15PxFromBottomAndLessThanLeftEdge_ShouldChangeCursorPositionTo15PxFromBottomAndLeftEdges)
{
    const QPointF expectedMousePos{ 15, def::sceneHeight - 15 };
    QMouseEvent mouseMoveEventBottomLeft{ getMouseEvent({ 14, def::sceneHeight - 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventBottomLeft);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, mouseMoveEvent_CursorMoreThan15PxFromBottomAndRightEdges_ShouldChangeCursorPositionTo15PxFromBottomAndRightEdges)
{
    const QPointF expectedMousePos{ def::sceneWidth - 15, def::sceneHeight - 15 };
    QMouseEvent mouseMoveEventBottomRight{ getMouseEvent({ def::sceneWidth - 14, def::sceneHeight - 14 }) };
    EXPECT_CALL(*cursorControllerMock, setCursorPosition(_)).Times(1);
    ControlPlaneTestable controller{ &displayWidget, std::move(cursorControllerMock) };
    controller.activate();

    controller.mouseMoveEvent(&mouseMoveEventBottomRight);

    EXPECT_THAT(controller.getMovePosition(), Eq(expectedMousePos));
}

TEST_F(ControlPlaneTests, LeaveEvent_DeactivatedControlKeyboardMode_ShouldNotSendMouseLeaveWindowSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTestable::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTests, LeaveEvent_DeactivatedControlMouseMode_ShouldNotSendMouseLeaveWindowSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTestable::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTests, LeaveEvent_ActivatedControlKeyboardMode_ShouldNotSendMouseLeaveWindowSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTestable::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTests, LeaveEvent_ActivatedControlMouseMode_ShouldSendMouseLeaveWindowSignal)
{
    ControlPlaneTestable controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTestable::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(1, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTests, KeyPressEvent_DeactivatedKeyEscPressed_ShouldNotSendSignalEscKeyPressed)
{
    ControlPlaneTestable controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_Escape,
                    Qt::NoModifier);
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTestable::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);

    EXPECT_EQ(0, escKeyPressedSignal.count());
}
/*
TEST_F(ControlPlaneTests, KeyboardPressControlInMouseMode_KeyAPressed_ShouldNotSendSignalEscKeyPressed)
{
    ControlPlaneTestable controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        Qt::Key_A,
        Qt::NoModifier
    );
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTestable::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyboardPressControlInMouseMode(&event);

    EXPECT_EQ(0, escKeyPressedSignal.count());
}

TEST_F(ControlPlaneTests, KeyboardPressControlInMouseMode_KeyEscPressed_ShouldSendSignalEscKeyPressed)
{
    ControlPlaneTestable controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        Qt::Key_Escape,
        Qt::NoModifier
    );
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTestable::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyboardPressControlInMouseMode(&event);

    EXPECT_EQ(1, escKeyPressedSignal.count());
}

typedef std::tr1::tuple<Qt::Key, int, int, int, bool, bool, bool, bool, QPointF> input_keyboard_pressed_params;

class ControlPlaneKeyboardPressedParamTestsClass : public TestWithParam<input_keyboard_pressed_params>
{
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
    }
};

TEST_P(ControlPlaneKeyboardPressedParamTestsClass, KeyboardPressControlInKeyboardMode_KeyPressed_ShouldWorkCorrect)
{
    const Qt::Key inputKey = std::tr1::get<0>(GetParam());
    const int expectedChangeMovePositionSignalCount = std::tr1::get<1>(GetParam());
    const int expectedStartFireSignalCount = std::tr1::get<2>(GetParam());
    const int expectedEscKeyPressedSignalCount = std::tr1::get<3>(GetParam());
    const bool expectedKeyMoveUpPressed = std::tr1::get<4>(GetParam());
    const bool expectedKeyMoveDownPressed = std::tr1::get<5>(GetParam());
    const bool expectedKeyMoveLeftPressed = std::tr1::get<6>(GetParam());
    const bool expectedKeyMoveRightPressed = std::tr1::get<7>(GetParam());
    const QPointF expectedMovePosition = std::tr1::get<8>(GetParam());
    ControlPlaneTestable controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        inputKey,
        Qt::NoModifier
    );
    QSignalSpy signalChangeMovePosition(&controller, &ControlPlaneTestable::changeMovePosition);
    QSignalSpy signalStartFire(&controller, &ControlPlaneTestable::startFire);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTestable::escKeyPressed);
    signalEscKeyPressed.wait(utdef::minSignalTimeDelay);

    controller.keyboardPressControlInKeyboardMode(&event);

    EXPECT_EQ(expectedChangeMovePositionSignalCount, signalChangeMovePosition.count());
    EXPECT_EQ(expectedStartFireSignalCount, signalStartFire.count());
    EXPECT_EQ(expectedEscKeyPressedSignalCount, signalEscKeyPressed.count());
    EXPECT_EQ(expectedKeyMoveUpPressed, controller.getKeyMoveUpPressed());
    EXPECT_EQ(expectedKeyMoveDownPressed, controller.getKeyMoveDownPressed());
    EXPECT_EQ(expectedKeyMoveLeftPressed, controller.getKeyMoveLeftPressed());
    EXPECT_EQ(expectedKeyMoveRightPressed, controller.getKeyMoveRightPressed());
    QPointF resultMovePosition = controller.getMovePosition();
    EXPECT_FLOAT_EQ(expectedMovePosition.x(), resultMovePosition.x());
    EXPECT_FLOAT_EQ(expectedMovePosition.y(), resultMovePosition.y());
}

INSTANTIATE_TEST_SUITE_P(
    PressKey,
    ControlPlaneKeyboardPressedParamTestsClass,
    Values(
        std::tr1::make_tuple(
            Qt::Key_Q,
            0,
            0,
            0,
            false,
            false,
            false,
            false,
            QPointF(def::halfSceneWidth, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_Space,
            0,
            1,
            0,
            false,
            false,
            false,
            false,
            QPointF(def::halfSceneWidth, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_Escape,
            0,
            0,
            1,
            false,
            false,
            false,
            false,
            QPointF(def::halfSceneWidth, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_W,
            1,
            0,
            0,
            true,
            false,
            false,
            false,
            QPointF(def::halfSceneWidth, 0)
        ),
        std::tr1::make_tuple(
            Qt::Key_Up,
            1,
            0,
            0,
            true,
            false,
            false,
            false,
            QPointF(def::halfSceneWidth, 0)
        ),
        std::tr1::make_tuple(
            Qt::Key_S,
            1,
            0,
            0,
            false,
            true,
            false,
            false,
            QPointF(def::halfSceneWidth, def::sceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_Down,
            1,
            0,
            0,
            false,
            true,
            false,
            false,
            QPointF(def::halfSceneWidth, def::sceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_A,
            1,
            0,
            0,
            false,
            false,
            true,
            false,
            QPointF(0, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_Left,
            1,
            0,
            0,
            false,
            false,
            true,
            false,
            QPointF(0, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_D,
            1,
            0,
            0,
            false,
            false,
            false,
            true,
            QPointF(def::sceneWidth, def::halfSceneHeight)
        ),
        std::tr1::make_tuple(
            Qt::Key_Right,
            1,
            0,
            0,
            false,
            false,
            false,
            true,
            QPointF(def::sceneWidth, def::halfSceneHeight)
        )
    )
);

typedef std::tr1::tuple<Qt::Key, bool, bool, bool, bool, int, int, int, bool, bool, bool, bool> input_keyboard_released_params;

class ControlPlaneKeyboardReleasedParamTestsClass : public TestWithParam<input_keyboard_released_params>
{
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
    }
};

TEST_P(ControlPlaneKeyboardReleasedParamTestsClass, KeyboardReleaseControlInKeyboardMode_KeyReleased_ShouldWorkCorrect)
{
    const Qt::Key inputKey = std::tr1::get<0>(GetParam());
    const bool inputKeyMoveUpPressed = std::tr1::get<1>(GetParam());
    const bool inputKeyMoveDownPressed = std::tr1::get<2>(GetParam());
    const bool inputKeyMoveLeftPressed = std::tr1::get<3>(GetParam());
    const bool inputKeyMoveRightPressed = std::tr1::get<4>(GetParam());
    const int expectedStopMoveOnAxeXSignalCount = std::tr1::get<5>(GetParam());
    const int expectedStopMoveOnAxeYSignalCount = std::tr1::get<6>(GetParam());
    const int expectedStopFireSignalCount = std::tr1::get<7>(GetParam());
    const bool expectedKeyMoveUpPressed = std::tr1::get<8>(GetParam());
    const bool expectedKeyMoveDownPressed = std::tr1::get<9>(GetParam());
    const bool expectedKeyMoveLeftPressed = std::tr1::get<10>(GetParam());
    const bool expectedKeyMoveRightPressed = std::tr1::get<11>(GetParam());
    ControlPlaneTestable controller(&displayWidget);
    controller.setKeyMoveUpPressed(inputKeyMoveUpPressed);
    controller.setKeyMoveDownPressed(inputKeyMoveDownPressed);
    controller.setKeyMoveLeftPressed(inputKeyMoveLeftPressed);
    controller.setKeyMoveRightPressed(inputKeyMoveRightPressed);
    QKeyEvent event(
        QEvent::KeyRelease,
        inputKey,
        Qt::NoModifier
    );
    QSignalSpy signalStopMoveOnAxeX(&controller, &ControlPlaneTestable::stopMoveOnAxeX);
    QSignalSpy signalStopMoveOnAxeY(&controller, &ControlPlaneTestable::stopMoveOnAxeY);
    QSignalSpy signalStopFire(&controller, &ControlPlaneTestable::stopFire);
    signalStopFire.wait(utdef::minSignalTimeDelay);

    controller.keyboardReleaseControlInKeyboardMode(&event);

    EXPECT_EQ(expectedStopMoveOnAxeXSignalCount, signalStopMoveOnAxeX.count());
    EXPECT_EQ(expectedStopMoveOnAxeYSignalCount, signalStopMoveOnAxeY.count());
    EXPECT_EQ(expectedStopFireSignalCount, signalStopFire.count());
    EXPECT_EQ(expectedKeyMoveUpPressed, controller.getKeyMoveUpPressed());
    EXPECT_EQ(expectedKeyMoveDownPressed, controller.getKeyMoveDownPressed());
    EXPECT_EQ(expectedKeyMoveLeftPressed, controller.getKeyMoveLeftPressed());
    EXPECT_EQ(expectedKeyMoveRightPressed, controller.getKeyMoveRightPressed());
}

INSTANTIATE_TEST_SUITE_P(
    ReleaseKey,
    ControlPlaneKeyboardReleasedParamTestsClass,
    Values(
        std::tr1::make_tuple(
            Qt::Key_Q,
            false,
            false,
            false,
            false,
            1,
            1,
            0,
            false,
            false,
            false,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_Space,
            true,
            true,
            true,
            true,
            0,
            0,
            1,
            true,
            true,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_W,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            false,
            true,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_Up,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            false,
            true,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_W,
            true,
            false,
            true,
            true,
            0,
            1,
            0,
            false,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_Up,
            true,
            false,
            true,
            true,
            0,
            1,
            0,
            false,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_S,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_Down,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_S,
            false,
            true,
            true,
            true,
            0,
            1,
            0,
            false,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_Down,
            false,
            true,
            true,
            true,
            0,
            1,
            0,
            false,
            false,
            true,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_A,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            true,
            false,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_Left,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            true,
            false,
            true
        ),
        std::tr1::make_tuple(
            Qt::Key_A,
            true,
            true,
            true,
            false,
            1,
            0,
            0,
            true,
            true,
            false,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_Left,
            true,
            true,
            true,
            false,
            1,
            0,
            0,
            true,
            true,
            false,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_D,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            true,
            true,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_Right,
            true,
            true,
            true,
            true,
            0,
            0,
            0,
            true,
            true,
            true,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_D,
            true,
            true,
            false,
            true,
            1,
            0,
            0,
            true,
            true,
            false,
            false
        ),
        std::tr1::make_tuple(
            Qt::Key_Right,
            true,
            true,
            false,
            true,
            1,
            0,
            0,
            true,
            true,
            false,
            false
        )
    )
);
*/
