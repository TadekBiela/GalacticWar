#include "rewardmodel.hpp"
#include "animationeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

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

    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                m_image->height(),
                                m_image->height()));
}

void RewardModel::destroy()
{
    this->scene()->removeItem(this);
    delete this;
}
