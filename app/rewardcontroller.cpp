
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


#include "randomgenerator.hpp"
#include "rewardcontroller.hpp"
#include "rewardcoinmodel.hpp"
#include "rewardspecialmodel.hpp"

const int RewardController::s_minCoinsInTier[def::maxTier] = { 1, 1, 2, 2, 3, 3 };
const int RewardController::s_maxCoinsInTier[def::maxTier] = { 3, 4, 5, 5, 5, 6 };
const int RewardController::s_coinTypeInTier[def::maxTier][10] =
  { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 1, 1, 1, 2 },
    { 0, 0, 1, 1, 1, 1, 1, 2, 2, 2 },
    { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
    { 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 } };
const int RewardController::s_specialChanceInTier[def::maxTier] = { 5, 10, 12, 15, 18, 22 };

RewardController::RewardController(GameplayView* view)
    : m_generator(new RandomGenerator)
{
    connect(this, SIGNAL(addRewardToScene(GameObject*)),
            view, SLOT(addGameObjectToScene(GameObject*)));
}

RewardController::~RewardController()
{
    delete m_generator;
}

void RewardController::spawnRewards(QPointF position, int tier)
{
    int rewardTierIdx = tier - 1;
    int numOfCoins    = m_generator->bounded(s_minCoinsInTier[rewardTierIdx],
                                             s_maxCoinsInTier[rewardTierIdx]);
    for (int i = 0; i < numOfCoins; i++)
    {
        coin_type type = static_cast<coin_type>(s_coinTypeInTier[rewardTierIdx][m_generator->bounded(0, 9)]);

        RewardCoinModel* coin = new RewardCoinModel(type);

        int xOffset = m_generator->bounded(def::minRewardPosOffset, def::maxRewardPosOffset);
        int yOffset = m_generator->bounded(def::minRewardPosOffset, def::maxRewardPosOffset);
        coin->setCenterPosition((position.x() + xOffset),
                                (position.y() + yOffset));

        connect(coin, SIGNAL(collected(coin_type)),
                this, SLOT(coinCollected(coin_type)));
        emit addRewardToScene(coin);
    }

    int specialChanse = m_generator->bounded(1, 100);

    if(specialChanse <= s_specialChanceInTier[rewardTierIdx])
    {
        special_type type = static_cast<special_type>(m_generator->bounded(1, def::maxNumOfSpecialRewards));

        RewardSpecialModel* special = new RewardSpecialModel(type);
        special->setCenterPosition(position);

        connect(special, SIGNAL(collected(special_type)),
                this, SLOT(specialCollected(special_type)));
        emit addRewardToScene(special);
    }
}

void RewardController::coinCollected(coin_type coin)
{
    emit rewardCoinCollected(coin);
}

void RewardController::specialCollected(special_type special)
{
    emit rewardSpecialCollected(special);
}
