#ifndef CONTROLPLANE_HPP
#define CONTROLPLANE_HPP

#include "settings.hpp"
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
    void applyNewSettings(Settings newSettings);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
    void keyPressEvent(QKeyEvent* event);

protected:
    void changeCursorToArrow();
    void changeCursorToCross();

    QWidget*         m_displayWidget;
    QGraphicsScene   m_scene;
    controller_state m_state;
    QPixmap          m_arrowCursorMap;
    QPixmap          m_crossCursorMap;
    control_type m_controlType;
};

#endif // CONTROLPLANE_HPP
