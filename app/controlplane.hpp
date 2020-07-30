#ifndef CONTROLPLANE_HPP
#define CONTROLPLANE_HPP

#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

enum controller_state
{
    activated = 0,
    deactivated = 1
};

class ControlPlane : public QGraphicsView
{
    Q_OBJECT
public:
    ControlPlane(QWidget* displayWidget);
    virtual ~ControlPlane();

signals:
    void mousePressed();
    void mouseReleased();
    void mouseMoved(QPointF currentMousePosition);
    void mouseLeaveWindow();
    void escKeyPressed();

public slots:
    void activate();
    void deactivate();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
    void keyPressEvent(QKeyEvent* event);

protected:
    QGraphicsScene   m_scene;
    controller_state m_state;
};

#endif // CONTROLPLANE_HPP
