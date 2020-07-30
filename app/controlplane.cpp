#include "controlplane.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"

ControlPlane::ControlPlane(QWidget* displayWidget)
    : QGraphicsView(displayWidget),
      m_displayWidget(displayWidget),
      m_scene(0, 0, def::sceneWight, def::sceneHeight, this),
      m_state(controller_state::deactivated),
      m_arrowCursorMap(),
      m_crossCursorMap()
{
    m_scene.setBackgroundBrush(QBrush(Qt::transparent));

    m_arrowCursorMap.convertFromImage(*g_imageStorage->getImage("arrow_cursor"));
    m_crossCursorMap.convertFromImage(*g_imageStorage->getImage("cross_cursor"));

    this->setScene(&m_scene);
    this->setStyleSheet("background: transparent;");
    this->setBackgroundBrush(QBrush(Qt::transparent));
    this->setGeometry(1, 1, def::sceneWight + 2, def::sceneHeight + 2);
    this->setMouseTracking(true);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->show();

    changeCursorToArrow();
}

ControlPlane::~ControlPlane()
{

}

void ControlPlane::activate()
{
    m_state = controller_state::activated;
    this->grabKeyboard();
    changeCursorToCross();
}

void ControlPlane::deactivate()
{
    m_state = controller_state::deactivated;
    this->releaseKeyboard();
    changeCursorToArrow();
}

void ControlPlane::mousePressEvent(QMouseEvent* event)
{
    if(Qt::MouseButton::LeftButton == event->button() &&
       controller_state::activated == m_state)
    {
        emit mousePressed();
    }
}

void ControlPlane::mouseReleaseEvent(QMouseEvent* event)
{
    if(Qt::MouseButton::LeftButton == event->button() &&
       controller_state::activated == m_state)
    {
        emit mouseReleased();
    }
}

void ControlPlane::mouseMoveEvent(QMouseEvent* event)
{
    if(controller_state::activated == m_state)
    {
        emit mouseMoved(event->pos());
    }
}

void ControlPlane::leaveEvent(QEvent* event)
{
    if(controller_state::activated == m_state)
    {
        event->ignore();
        emit mouseLeaveWindow();
    }
}

void ControlPlane::keyPressEvent(QKeyEvent* event)
{
    if(Qt::Key_Escape == event->key() &&
       controller_state::activated == m_state)
    {
        emit escKeyPressed();
    }
}

void ControlPlane::changeCursorToArrow()
{
    QCursor arrowCursor(m_arrowCursorMap, 0, 0);
    m_displayWidget->setCursor(arrowCursor);
}

void ControlPlane::changeCursorToCross()
{
    QCursor crossCursor(m_crossCursorMap, 0, 0);
    m_displayWidget->setCursor(crossCursor);
}
