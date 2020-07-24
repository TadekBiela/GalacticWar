#include "controlplane.hpp"
#include "definitions.hpp"

ControlPlane::ControlPlane(QWidget* displayWidget)
    : QGraphicsView(displayWidget),
      m_scene(0, 0, def::sceneWight, def::sceneHeight, this)
{
    m_scene.setBackgroundBrush(QBrush(Qt::transparent));
    this->setScene(&m_scene);
    this->setStyleSheet("background: transparent;");
    this->setBackgroundBrush(QBrush(Qt::transparent));
    this->setGeometry(1, 1, def::sceneWight + 2, def::sceneHeight + 2);
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->show();
}

ControlPlane::~ControlPlane()
{

}

void ControlPlane::mousePressEvent(QMouseEvent* event)
{
    if(Qt::MouseButton::LeftButton == event->button())
    {
        emit mousePressed();
    }
}

void ControlPlane::mouseReleaseEvent(QMouseEvent* event)
{
    if(Qt::MouseButton::LeftButton == event->button())
    {
        emit mouseReleased();
    }
}

void ControlPlane::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoved(event->pos());
}

void ControlPlane::leaveEvent(QEvent* event)
{
    event->ignore();
    emit mouseLeaveWindow();
}

void ControlPlane::keyPressEvent(QKeyEvent* event)
{
    if(Qt::Key_Escape == event->key())
    {
        emit escKeyPressed();
    }
}
