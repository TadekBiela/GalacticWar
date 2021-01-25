
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


#ifndef CONTROLPLANE_HPP
#define CONTROLPLANE_HPP

#include "settings.hpp"
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

enum class controller_state {
    activated,
    deactivated
};

class ControlPlane;

typedef void (ControlPlane::*keyboardControlFuncPrt)(QKeyEvent*);

class ControlPlane : public QGraphicsView
{
    Q_OBJECT
public:
    ControlPlane(QWidget* displayWidget);
    virtual ~ControlPlane();

signals:
    void startFire();
    void stopFire();
    void stopMoveOnAxeX();
    void stopMoveOnAxeY();
    void changeMovePosition(QPointF movePosition);
    void mouseLeaveWindow();
    void escKeyPressed();

public slots:
    void activate();
    void deactivate();
    void applyNewSettings(Settings newSettings);
    void setMovePosition(QPointF movePosition);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

protected:
    void changeToMenuCursor();
    void changeToGameCursor();
    void switchControlToMouseMode();
    void switchControlToKeyboardMode();
    void keyboardPressControlInMouseMode(QKeyEvent* event);
    void keyboardReleaseControlInMouseMode(QKeyEvent* event);
    void keyboardPressControlInKeyboardMode(QKeyEvent* event);
    void keyboardReleaseControlInKeyboardMode(QKeyEvent* event);

    QWidget* m_displayWidget;
    QGraphicsScene m_scene;
    controller_state m_state;
    QPixmap m_arrowCursorMap;
    QPixmap m_crossCursorMap;
    control_mode m_controlMode;
    QPointF m_movePosition;
    keyboardControlFuncPrt m_keyboardPressControl;
    keyboardControlFuncPrt m_keyboardReleaseControl;
    bool m_keyMoveUpPressed;
    bool m_keyMoveDownPressed;
    bool m_keyMoveLeftPressed;
    bool m_keyMoveRightPressed;
};

#endif // CONTROLPLANE_HPP
