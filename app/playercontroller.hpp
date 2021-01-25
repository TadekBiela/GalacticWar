
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


#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP

#include "controlplane.hpp"
#include "gameobject.hpp"
#include "gameplayview.hpp"
#include "playermodel.hpp"
#include "rewardtypes.hpp"
#include <QObject>

class PlayerController : public QObject
{
    Q_OBJECT
public:
    PlayerController(ControlPlane* controller,
                     GameplayView* view);
    virtual ~PlayerController();

signals:
    void addPlayerToScene(GameObject* player);
    void addHealthPoints(int healthPoints);
    void subtractHealthPoints(int healthPoints);

public slots:
    void create();
    void destroy();
    void changePlayerAtribute(special_type reward);
    void addHealth(int healthPoints);
    void subtractHealth(int healthPoints);

protected:
    ControlPlane* m_controller;
    PlayerModel*  m_model;
};

#endif // PLAYERCONTROLLER_HPP
