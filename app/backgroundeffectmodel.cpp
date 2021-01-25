
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


#include "backgroundeffectmodel.hpp"
#include "functions.hpp"

struct BackgroundEffect
{
    QString name;
    int     animationFrameWidth;
    int     animationFrameHeight;
    int     numOfFrames;
    int     moveTimeDelay;
};

const BackgroundEffect BackgroundEffectModel::s_backgroundEffectsConfig[background_effect::last_element + 1] = {
    { "star",  32, 32, 20, 20 },
    { "star2", 32, 32, 10, 20 },
    { "star3", 32, 32,  5, 15 },
    { "comet",  4, 56,  7,  5 }
};

BackgroundEffectModel::BackgroundEffectModel(background_effect type,
                                             QPointF           startPosition,
                                             int               moveDirection,
                                             QGraphicsScene*   targetScene)
    : AnimationEffectModel(s_backgroundEffectsConfig[type].name,
                           startPosition,
                           s_backgroundEffectsConfig[type].animationFrameWidth,
                           s_backgroundEffectsConfig[type].animationFrameHeight,
                           s_backgroundEffectsConfig[type].numOfFrames,
                           targetScene),
      m_moveDirection(moveDirection),
      m_moveTimer()
{
    setRotation(m_moveDirection);
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    m_moveTimer.setInterval(s_backgroundEffectsConfig[type].moveTimeDelay);
}

BackgroundEffectModel::~BackgroundEffectModel()
{

}

void BackgroundEffectModel::play()
{
    AnimationEffectModel::play();
    m_moveTimer.start();
}

void BackgroundEffectModel::move()
{
    QPointF newPosition = moveForward(pos(), m_moveDirection);
    this->setPos(newPosition);

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
    }
}

void BackgroundEffectModel::start() {
    AnimationEffectModel::start();
    m_moveTimer.start();
}

void BackgroundEffectModel::stop() {
    AnimationEffectModel::stop();
    m_moveTimer.stop();
}

