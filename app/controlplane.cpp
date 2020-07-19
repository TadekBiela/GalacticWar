#include "controlplane.hpp"

ControlPlane::ControlPlane(QWidget* displayWidget)
                            : QGraphicsView(displayWidget)
{
    setMouseTracking(true);
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
