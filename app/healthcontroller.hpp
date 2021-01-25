
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


#ifndef HEALTHCONTROLLER_HPP
#define HEALTHCONTROLLER_HPP

#include "barview.hpp"
#include "controlplane.hpp"
#include "healthmodel.hpp"
#include <QObject>
#include <QWidget>

class HealthController : public QObject
{
    Q_OBJECT
public:
    HealthController(QWidget*      displayWidget,
                     ControlPlane* controller);
    virtual ~HealthController();

signals:
    void noHealth();

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void addHealthPoints(int healthPoints);
    void subtractHealthPoints(int healthPoints);

protected:
    QWidget*      m_displayWidget;
    ControlPlane* m_controller;
    HealthModel*  m_model;
    BarView*      m_view;

};

#endif // HEALTHCONTROLLER_HPP
