#include "rewardspecialmodel.hpp"
#include "definitions.hpp"

RewardSpecialModel::RewardSpecialModel(special_type type)
                                        : m_type(type)
{
    //temporary simple graphic
    QPixmap map(QSize(30, 30));
    map.fill(Qt::cyan);
    setPixmap(map);
}

RewardSpecialModel::~RewardSpecialModel()
{

}

void RewardSpecialModel::collect()
{
    emit collected(m_type);
    destroy();
}

void RewardSpecialModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }
}
