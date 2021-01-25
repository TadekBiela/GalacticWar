
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


#ifndef GAMEPLAYVIEW_HPP
#define GAMEPLAYVIEW_HPP

#include "gameobject.hpp"
#include "graphicsview.hpp"

class GameplayView : public GraphicsView
{
    Q_OBJECT
public:
    GameplayView(QWidget* displayWidget);
    virtual ~GameplayView();
    void startAllItems() override;
    void stopAllItems() override;

public slots:
    void activate() override;
    void deactivate() override;
    void addGameObjectToScene(GameObject* object);
    void removeAllGameObjects();
};

#endif // GAMEPLAYVIEW_HPP
