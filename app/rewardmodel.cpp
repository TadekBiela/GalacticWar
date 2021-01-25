
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


#include "rewardmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

RewardModel::RewardModel()
    : GameObject(game_object_type::reward),
      m_animationFrameIdx(0)
{
    connect(&m_animationTimer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(&m_destroyTimer,   SIGNAL(timeout()), this, SLOT(destroy()));
    m_animationTimer.setInterval(def::animationFrameDuration);
    m_destroyTimer.setInterval(def::defaultRewardDestroyTimeDelay);
    m_animationTimer.start();
    m_destroyTimer.start();
}

RewardModel::~RewardModel()
{

}

void RewardModel::start()
{
    m_animationTimer.start();
    m_destroyTimer.start();
}

void RewardModel::stop()
{
    m_animationTimer.stop();
    m_destroyTimer.stop();
}

void RewardModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }

    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_image->height(),
                                m_image->height()));
}

void RewardModel::destroy()
{
    this->scene()->removeItem(this);
    delete this;
}
