
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


#include "gameplayview.hpp"

GameplayView::GameplayView(QWidget* displayWidget)
    : GraphicsView(displayWidget)
{

}

GameplayView::~GameplayView()
{

}

void GameplayView::startAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        GameObject* object = dynamic_cast<GameObject*>(*it);
        object->start();
    }
}

void GameplayView::stopAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        GameObject* object = dynamic_cast<GameObject*>(*it);
        object->stop();
    }
}

void GameplayView::activate()
{
    startAllItems();
    setGraphicsEffects(0, 0);
}

void GameplayView::deactivate()
{
    stopAllItems();
    setGraphicsEffects(0.5, 5);
}

void GameplayView::addGameObjectToScene(GameObject* object)
{
    m_scene.addItem(dynamic_cast<QGraphicsItem*>(object));
}

void GameplayView::removeAllGameObjects()
{
    m_scene.clear();
    setGraphicsEffects(0, 0);
}
