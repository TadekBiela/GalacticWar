
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


#include "rewardcoinmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "imagestorage.hpp"
#include "soundeffectmodel.hpp"

RewardCoinModel::RewardCoinModel(coin_type type)
    : m_type(type)
{
    QString animationName;
    switch (m_type)
    {
        case bronze:
            animationName = "coin1";
            break;
        case silver:
            animationName = "coin2";
            break;
        case gold:
            animationName = "coin3";
            break;
    }

    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_image->height(),
                                m_image->height()));
}

RewardCoinModel::~RewardCoinModel()
{

}

void RewardCoinModel::collect()
{
    emit collected(m_type);
    QPointF collectedRewardPosition = getCenterPosition();
    AnimationEffectModel* collectAnim = new AnimationEffectModel("collect_reward",
                                                                 collectedRewardPosition,
                                                                 def::animationSmallFrameWidth,
                                                                 def::animationSmallFrameHeight);
    collectAnim->play();
    SoundEffectModel* collectSound = new SoundEffectModel("collect_coin");
    collectSound->play();
    destroy();
}
