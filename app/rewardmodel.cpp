#include "rewardmodel.hpp"
#include "definitions.hpp"

RewardModel::RewardModel()
                         : m_animationFrameIdx(0)
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

QPixmap RewardModel::getAnimationFrame()
{
    QPixmap map;
    map.convertFromImage(m_image.copy(m_animationFrameIdx * def::animationSmallFrameWight,
                                      0,
                                      def::animationSmallFrameWight,
                                      def::animationSmallFrameHeight));
    return map;
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

    setPixmap(getAnimationFrame());
}

void RewardModel::destroy()
{
    delete this;
}
