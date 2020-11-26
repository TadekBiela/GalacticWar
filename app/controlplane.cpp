#include "controlplane.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"

ControlPlane::ControlPlane(QWidget* displayWidget)
    : QGraphicsView(displayWidget),
      m_displayWidget(displayWidget),
      m_scene(0, 0, def::sceneWidth, def::sceneHeight, this),
      m_state(controller_state::deactivated),
      m_arrowCursorMap(),
      m_crossCursorMap(),
      m_movePosition(def::halfSceneWidth, def::halfSceneHeight),
      m_keyMoveUpPressed(false),
      m_keyMoveDownPressed(false),
      m_keyMoveLeftPressed(false),
      m_keyMoveRightPressed(false)
{
    m_scene.setBackgroundBrush(QBrush(Qt::transparent));

    m_arrowCursorMap.convertFromImage(*g_imageStorage->getImage("arrow_cursor"));
    m_crossCursorMap.convertFromImage(*g_imageStorage->getImage("cross_cursor"));

    this->setScene(&m_scene);
    this->setStyleSheet("background: transparent;");
    this->setBackgroundBrush(QBrush(Qt::transparent));
    this->setGeometry(1, 1, def::sceneWidth + 2, def::sceneHeight + 2);
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->show();

    changeToMenuCursor();
    m_controlMode = control_mode::mouse;
    switchControlToMouseMode();
    deactivate();
}

ControlPlane::~ControlPlane()
{

}

void ControlPlane::activate()
{
    m_state = controller_state::activated;
    this->grabKeyboard();
    changeToGameCursor();
}

void ControlPlane::deactivate()
{
    m_state = controller_state::deactivated;
    this->releaseKeyboard();
    changeToMenuCursor();
}

void ControlPlane::applyNewSettings(Settings newSettings) {
    m_controlMode = newSettings.controlMode;

    if(control_mode::mouse == m_controlMode) {
        switchControlToMouseMode();
    }
    else {
        switchControlToKeyboardMode();
    }

}

void ControlPlane::setMovePosition(QPointF movePosition) {
    m_movePosition = movePosition;
}

void ControlPlane::mousePressEvent(QMouseEvent* event)
{
    if(controller_state::activated == m_state &&
       control_mode::mouse == m_controlMode &&
       Qt::MouseButton::LeftButton == event->button()) {
        emit startFire();
    }
    event->ignore();
}

void ControlPlane::mouseReleaseEvent(QMouseEvent* event)
{
    if(controller_state::activated == m_state &&
       control_mode::mouse == m_controlMode &&
       Qt::MouseButton::LeftButton == event->button()) {
        emit stopFire();
    }
    event->ignore();
}

void ControlPlane::mouseMoveEvent(QMouseEvent* event)
{
    if(controller_state::activated == m_state &&
       control_mode::mouse == m_controlMode) {
        m_movePosition = event->pos();
        emit changeMovePosition(m_movePosition);
    }
    event->ignore();
}

void ControlPlane::leaveEvent(QEvent* event)
{
    if(controller_state::activated == m_state &&
       control_mode::mouse == m_controlMode) {
        emit mouseLeaveWindow();
    }
    event->ignore();
}

void ControlPlane::keyPressEvent(QKeyEvent* event)
{
    if(controller_state::activated == m_state) {
        (this->*m_keyboardPressControl)(event);
    }
}

void ControlPlane::keyReleaseEvent(QKeyEvent* event)
{
    if(controller_state::activated == m_state) {
        (this->*m_keyboardReleaseControl)(event);
    }
}

void ControlPlane::changeToMenuCursor()
{
    QCursor arrowCursor(m_arrowCursorMap, 0, 0);
    m_displayWidget->setCursor(arrowCursor);
}

void ControlPlane::changeToGameCursor()
{
    if(control_mode::mouse == m_controlMode) {
        QCursor crossCursor(m_crossCursorMap, 0, 0);
        m_displayWidget->setCursor(crossCursor);
    }
    else {
        QCursor hiddenCursor(QPixmap(1, 1), 0, 0);
        m_displayWidget->setCursor(hiddenCursor);
    }
}

void ControlPlane::switchControlToMouseMode() {
    m_keyboardPressControl = &this->keyboardPressControlInMouseMode;
    m_keyboardReleaseControl = &this->keyboardReleaseControlInMouseMode;
}

void ControlPlane::switchControlToKeyboardMode() {
    m_keyboardPressControl = &this->keyboardPressControlInKeyboardMode;
    m_keyboardReleaseControl = &this->keyboardReleaseControlInKeyboardMode;
}

void ControlPlane::keyboardPressControlInMouseMode(QKeyEvent* event) {
    if(Qt::Key_Escape == event->key()) {
        emit escKeyPressed();
    }
    event->ignore();
}

void ControlPlane::keyboardReleaseControlInMouseMode(QKeyEvent* event) {
    event->ignore();
}

void ControlPlane::keyboardPressControlInKeyboardMode(QKeyEvent* event) {
    if(not event->isAutoRepeat()) {
        switch(event->key()) {
            case Qt::Key_W:
            case Qt::Key_Up:
                m_keyMoveUpPressed = true;
                m_movePosition.setY(0);
                emit changeMovePosition(m_movePosition);
                break;
            case Qt::Key_A:
            case Qt::Key_Left:
                m_keyMoveLeftPressed = true;
                m_movePosition.setX(0);
                emit changeMovePosition(m_movePosition);
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                m_keyMoveDownPressed = true;
                m_movePosition.setY(def::sceneHeight);
                emit changeMovePosition(m_movePosition);
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                m_keyMoveRightPressed = true;
                m_movePosition.setX(def::sceneWidth);
                emit changeMovePosition(m_movePosition);
                break;
            case Qt::Key_Space:
                emit startFire();
                break;
            case Qt::Key_Escape:
                emit escKeyPressed();
                break;
        }
    }
    event->ignore();
}

void ControlPlane::keyboardReleaseControlInKeyboardMode(QKeyEvent* event) {
    if(not event->isAutoRepeat()) {
        switch(event->key()) {
            case Qt::Key_W:
            case Qt::Key_Up:
                m_keyMoveUpPressed = false;
                break;
            case Qt::Key_A:
            case Qt::Key_Left:
                m_keyMoveLeftPressed = false;
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                m_keyMoveDownPressed = false;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                m_keyMoveRightPressed = false;
                break;
            case Qt::Key_Space:
                emit stopFire();
                break;
        }
        if(not m_keyMoveUpPressed && not m_keyMoveDownPressed) {
            emit stopMoveOnAxeY();
        }
        if(not m_keyMoveLeftPressed && not m_keyMoveRightPressed) {
            emit stopMoveOnAxeX();
        }
    }
    event->ignore();
}

