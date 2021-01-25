
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


#ifndef BACKGROUNDEFFECTMODEL_HPP
#define BACKGROUNDEFFECTMODEL_HPP

#include "animationeffectmodel.hpp"

enum background_effect
{
    first_element = 0,
    star          = 0,
    star2         = 1,
    star3         = 2,
    comet         = 3,
    last_element  = 3
};

struct BackgroundEffect;

class BackgroundEffectModel : public AnimationEffectModel
{
    Q_OBJECT
public:
    BackgroundEffectModel(background_effect type,
                          QPointF           startPosition,
                          int               moveDirection,
                          QGraphicsScene*   targetScene);
    virtual ~BackgroundEffectModel();
    void play() override;

private slots:
    void move();
    void start() override;
    void stop() override;

private:
    int    m_moveDirection;
    QTimer m_moveTimer;

    static const BackgroundEffect s_backgroundEffectsConfig[background_effect::last_element + 1];
};

#endif // BACKGROUNDEFFECTMODEL_HPP
