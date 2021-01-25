
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


#ifndef LEVELCONTROLLER_HPP
#define LEVELCONTROLLER_HPP

#include "controlplane.hpp"
#include "enemyconfiguration.hpp"
#include "labelview.hpp"
#include "levelmodel.hpp"
#include <QObject>
#include <QWidget>

class LevelController : public QObject
{
    Q_OBJECT
public:
    LevelController(QWidget*      displayWidget,
                    ControlPlane* controller);
    virtual ~LevelController();

signals:
    void changeEnemyConfig(EnemyConfiguration enemyConfig);

public slots:
    void create();
    void destroy();
    void show();
    void hide();
    void nextLevel();

protected:
    QWidget*      m_displayWidget;
    ControlPlane* m_controller;
    LevelModel*   m_model;
    LabelView*    m_view;
};

#endif // LEVELCONTROLLER_HPP
