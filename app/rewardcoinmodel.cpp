#include "rewardcoinmodel.hpp"
#include "definitions.hpp"

RewardCoinModel::RewardCoinModel(coin_type type)
                                  : m_type(type)
{

}

RewardCoinModel::~RewardCoinModel()
{

}

void RewardCoinModel::collect()
{
    emit collected(m_type);
    destroy();
}

void RewardCoinModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }
}
