#include "rewardcoinmodel.hpp"
#include "definitions.hpp"

RewardCoinModel::RewardCoinModel(coin_type type)
                                  : m_type(type)
{
    //temporary simple graphic
    QPixmap map(QSize(30, 30));

    switch (m_type)
    {
        case bronze:
            map.fill(Qt::darkRed);
            break;
        case silver:
            map.fill(Qt::gray);
            break;
        case gold:
            map.fill(Qt::yellow);
            break;
    }

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
