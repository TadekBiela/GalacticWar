
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


#ifndef ANIMATIONPLANEVIEW_HPP
#define ANIMATIONPLANEVIEW_HPP

#include "graphicsview.hpp"
#include <QWidget>

class AnimationEffectModel;

class AnimationPlaneView : public GraphicsView
{
    Q_OBJECT
public:
    AnimationPlaneView(QWidget* displayWidget);
    virtual ~AnimationPlaneView();
    virtual void startAllItems() override;
    virtual void stopAllItems()  override;

public slots:
    void activate()   override;
    void deactivate() override;
    void addEffectToScene(AnimationEffectModel* object);
};

extern AnimationPlaneView* g_animationPlaneView;

#endif // ANIMATIONPLANEVIEW_HPP
