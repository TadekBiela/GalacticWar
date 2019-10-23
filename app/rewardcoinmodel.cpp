#include "rewardcoinmodel.hpp"
#include "definitions.hpp"

RewardCoinModel::RewardCoinModel(coin_type type)
                                  : m_type(type)
{
    //temporary simple graphic
    QPixmap map(QSize(50, 50));
    map.fill(Qt::gray);
    setPixmap(map);
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
