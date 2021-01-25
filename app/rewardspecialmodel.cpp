
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


#include "rewardspecialmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include "soundeffectmodel.hpp"
#include "imagestorage.hpp"

RewardSpecialModel::RewardSpecialModel(special_type type)
    : m_type(type)
{
    QString animationName;
    switch (m_type)
    {
        case health:
            animationName = "health";
            m_soundName   = "collect_health";
            break;
        case weaponRed:
            animationName = "weapon_red";
            m_soundName   = "collect_weapon";
            break;
        case weaponYellow:
            animationName = "weapon_yellow";
            m_soundName   = "collect_weapon";
            break;
        case weaponBlue:
            animationName = "weapon_blue";
            m_soundName   = "collect_weapon";
            break;
    }

    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_image->height(),
                                m_image->height()));
}

RewardSpecialModel::~RewardSpecialModel()
{

}

void RewardSpecialModel::collect()
{
    emit collected(m_type);
    QPointF collectedRewardPosition = getCenterPosition();
    AnimationEffectModel* collectAnim = new AnimationEffectModel("collect_reward",
                                                                 collectedRewardPosition,
                                                                 def::animationSmallFrameWidth,
                                                                 def::animationSmallFrameHeight);
    collectAnim->play();
    SoundEffectModel* collectSound = new SoundEffectModel(m_soundName);
    collectSound->play();
    destroy();
}
