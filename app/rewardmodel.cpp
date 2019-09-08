#include "rewardmodel.hpp"
#include "definitions.hpp"

RewardModel::RewardModel() :
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

void RewardModel::destroy()
{
    delete this;
}
