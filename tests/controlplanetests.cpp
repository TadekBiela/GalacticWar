#include <gtest/gtest.h>
#include "utdefinitions.hpp"
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

class ControlPlaneTest : public ControlPlane
{
public:
    ControlPlaneTest(QWidget* displayWidget)
        : ControlPlane(displayWidget) {}
    virtual ~ControlPlaneTest() {}
    void keyboardPressControlInMouseMode(QKeyEvent* event) {
        ControlPlane::keyboardPressControlInMouseMode(event);
    }
    void keyboardPressControlInKeyboardMode(QKeyEvent* event) {
        ControlPlane::keyboardPressControlInKeyboardMode(event);
    }
    void keyboardReleaseControlInKeyboardMode(QKeyEvent* event) {
        ControlPlane::keyboardReleaseControlInKeyboardMode(event);
    }
    controller_state getState() const {
        return m_state;
    }
    control_mode getControlMode() const {
        return m_controlMode;
    }
    QPointF getMovePosition() const {
        return m_movePosition;
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

class ControlPlaneTestsClass : public testing::Test
{
public:
    void SetUp() {
        g_imageStorage = new ImageStorageStub;
    }
    void TearDown() {
        delete g_imageStorage;
    }
};

TEST_F(ControlPlaneTestsClass, Constructor_CreateNewObject_ShouldSetControlToMouseAndDeactivate)
{
    QWidget displayWidget;

    ControlPlaneTest controller(&displayWidget);

    EXPECT_EQ(controller_state::deactivated, controller.getState());
    EXPECT_EQ(control_mode::mouse, controller.getControlMode());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedControlKeyboardModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedControlMouseModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedControlKeyboardModeLeftButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_DeactivatedControlMouseModeLeftButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_ActivatedControlKeyboardModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_ActivatedControlMouseModeRightButtonPressed_ShouldNotSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(0, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MousePressEvent_ActivatedControlMouseModeLeftButtonPressed_ShouldSendStartFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonPress,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy startFireSignal(&controller, &ControlPlaneTest::startFire);
    startFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mousePressEvent(&event);

    EXPECT_EQ(1, startFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedControlKeyboardModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedControlMouseModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedControlKeyboardModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_DeactivatedControlMouseModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedControlKeyboardModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedControlMouseModeRightButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::RightButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedControlKeyboardModeLeftButtonReleased_ShouldNotSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(0, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, MouseReleaseEvent_ActivatedControlMouseModeLeftButtonReleased_ShouldSendStopFireSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QMouseEvent event(
        QEvent::MouseButtonRelease,
        QPointF(0,0),
        Qt::MouseButton::LeftButton,
        Qt::NoButton,
        Qt::NoModifier
    );
    QSignalSpy stopFireSignal(&controller, &ControlPlaneTest::stopFire);
    stopFireSignal.wait(utdef::minSignalTimeDelay);

    controller.mouseReleaseEvent(&event);

    EXPECT_EQ(1, stopFireSignal.count());
}

TEST_F(ControlPlaneTestsClass, LeaveEvent_DeactivatedControlKeyboardMode_ShouldNotSendMouseLeaveWindowSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::keyboard);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTest::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTestsClass, LeaveEvent_DeactivatedControlMouseMode_ShouldNotSendMouseLeaveWindowSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::deactivated);
    controller.setControlMode(control_mode::mouse);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTest::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTestsClass, LeaveEvent_ActivatedControlKeyboardMode_ShouldNotSendMouseLeaveWindowSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::keyboard);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTest::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(0, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTestsClass, LeaveEvent_ActivatedControlMouseMode_ShouldSendMouseLeaveWindowSignal)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setState(controller_state::activated);
    controller.setControlMode(control_mode::mouse);
    QEvent event(QEvent::Leave);
    QSignalSpy mouseLeaveWindowSignal(&controller, &ControlPlaneTest::mouseLeaveWindow);
    mouseLeaveWindowSignal.wait(utdef::minSignalTimeDelay);

    controller.leaveEvent(&event);

    EXPECT_EQ(1, mouseLeaveWindowSignal.count());
}

TEST_F(ControlPlaneTestsClass, KeyPressEvent_DeactivatedKeyEscPressed_ShouldNotSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(QEvent::KeyPress,
                    Qt::Key_Escape,
                    Qt::NoModifier);
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTest::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyPressEvent(&event);

    EXPECT_EQ(0, escKeyPressedSignal.count());
}

TEST_F(ControlPlaneTestsClass, KeyboardPressControlInMouseMode_KeyAPressed_ShouldNotSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        Qt::Key_A,
        Qt::NoModifier
    );
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTest::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyboardPressControlInMouseMode(&event);

    EXPECT_EQ(0, escKeyPressedSignal.count());
}

TEST_F(ControlPlaneTestsClass, KeyboardPressControlInMouseMode_KeyEscPressed_ShouldSendSignalEscKeyPressed)
{
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        Qt::Key_Escape,
        Qt::NoModifier
    );
    QSignalSpy escKeyPressedSignal(&controller, &ControlPlaneTest::escKeyPressed);
    escKeyPressedSignal.wait(utdef::minSignalTimeDelay);

    controller.keyboardPressControlInMouseMode(&event);

    EXPECT_EQ(1, escKeyPressedSignal.count());
}

typedef std::tr1::tuple<Qt::Key, int, int, int, bool, bool, bool, bool, QPointF> input_keyboard_pressed_params;

class ControlPlaneKeyboardPressedParamTestsClass : public testing::TestWithParam<input_keyboard_pressed_params>
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
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    QKeyEvent event(
        QEvent::KeyPress,
        inputKey,
        Qt::NoModifier
    );
    QSignalSpy signalChangeMovePosition(&controller, &ControlPlaneTest::changeMovePosition);
    QSignalSpy signalStartFire(&controller, &ControlPlaneTest::startFire);
    QSignalSpy signalEscKeyPressed(&controller, &ControlPlaneTest::escKeyPressed);
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
    testing::Values(
        std::tr1::make_tuple(
            Qt::Key_Q,
            0,
            0,
            0,
            false,
            false,
            false,
            false,
            QPointF(def::halfSceneWight, def::halfSceneHeight)
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
            QPointF(def::halfSceneWight, def::halfSceneHeight)
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
            QPointF(def::halfSceneWight, def::halfSceneHeight)
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
            QPointF(def::halfSceneWight, 0)
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
            QPointF(def::halfSceneWight, 0)
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
            QPointF(def::halfSceneWight, def::sceneHeight)
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
            QPointF(def::halfSceneWight, def::sceneHeight)
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
            QPointF(def::sceneWight, def::halfSceneHeight)
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
            QPointF(def::sceneWight, def::halfSceneHeight)
        )
    )
);

typedef std::tr1::tuple<Qt::Key, bool, bool, bool, bool, int, int, int, bool, bool, bool, bool> input_keyboard_released_params;

class ControlPlaneKeyboardReleasedParamTestsClass : public testing::TestWithParam<input_keyboard_released_params>
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
    QWidget displayWidget;
    ControlPlaneTest controller(&displayWidget);
    controller.setKeyMoveUpPressed(inputKeyMoveUpPressed);
    controller.setKeyMoveDownPressed(inputKeyMoveDownPressed);
    controller.setKeyMoveLeftPressed(inputKeyMoveLeftPressed);
    controller.setKeyMoveRightPressed(inputKeyMoveRightPressed);
    QKeyEvent event(
        QEvent::KeyRelease,
        inputKey,
        Qt::NoModifier
    );
    QSignalSpy signalStopMoveOnAxeX(&controller, &ControlPlaneTest::stopMoveOnAxeX);
    QSignalSpy signalStopMoveOnAxeY(&controller, &ControlPlaneTest::stopMoveOnAxeY);
    QSignalSpy signalStopFire(&controller, &ControlPlaneTest::stopFire);
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
    testing::Values(
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

