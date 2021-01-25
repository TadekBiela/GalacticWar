
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


#include "animationplaneview.hpp"
#include "animationeffectmodel.hpp"

AnimationPlaneView::AnimationPlaneView(QWidget* displayWidget)
    : GraphicsView(displayWidget)
{

}

AnimationPlaneView::~AnimationPlaneView()
{

}

void AnimationPlaneView::startAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        AnimationEffectModel* effect = dynamic_cast<AnimationEffectModel*>(*it);
        effect->start();
    }
}

void AnimationPlaneView::stopAllItems()
{
    auto items = m_scene.items();

    for(auto it = items.begin(); it != items.end(); it++)
    {
        AnimationEffectModel* effect = dynamic_cast<AnimationEffectModel*>(*it);
        effect->stop();
    }
}

void AnimationPlaneView::activate()
{
    startAllItems();
    setGraphicsEffects(0, 0);
}

void AnimationPlaneView::deactivate()
{
    stopAllItems();
    setGraphicsEffects(0.4, 4);
}

void AnimationPlaneView::addEffectToScene(AnimationEffectModel* object)
{
    m_scene.addItem(dynamic_cast<QGraphicsItem*>(object));
}

AnimationPlaneView* g_animationPlaneView;
