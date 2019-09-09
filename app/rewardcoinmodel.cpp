#include "rewardcoinmodel.hpp"
#include "definitions.hpp"

RewardCoinModel::RewardCoinModel(coin_type type) :
                                 m_type(type)
{

}

void RewardCoinModel::collect()
{

}

void RewardCoinModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }
}
