#ifndef CONTROLPLANE_HPP
#define CONTROLPLANE_HPP

#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

class ControlPlane : public QGraphicsView
{
    Q_OBJECT
public:
    ControlPlane(QWidget* displayWidget);
    virtual ~ControlPlane();

signals:
    void mousePressed();
    void mouseReleased();
    void mouseMoved(QPoint currentMousePosition);
    void mouseLeaveWindow();
    void escKeyPressed();

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
    void keyPressEvent(QKeyEvent* event);
};

#endif // CONTROLPLANE_HPP
