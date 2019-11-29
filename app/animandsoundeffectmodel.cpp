#include "animandsoundeffectmodel.hpp"
#include "definitions.hpp"
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>

AnimAndSoundEffectModel::AnimAndSoundEffectModel()
                                                 : m_isAnimEnabled(false),
                                                   m_animationFrameIdx(0),
                                                   m_isSoundEnabled(false)
{
    connect(&m_destroyTimer, SIGNAL(timeout()), this, SLOT(destroy()));
    m_destroyTimer.setInterval(def::animationFrameDuration * def::maxAnimationFrames);
    m_destroyTimer.start();
}

AnimAndSoundEffectModel::~AnimAndSoundEffectModel()
{

}

QPixmap AnimAndSoundEffectModel::getAnimationFrame()
{

}

void AnimAndSoundEffectModel::start()
{
    if(m_isAnimEnabled)
    {
        m_animationTimer.start();
    }
    if(m_isSoundEnabled)
    {
        m_sound.play();
    }
    m_destroyTimer.setInterval(m_remainigDestroyTime);
    m_destroyTimer.start();
}

void AnimAndSoundEffectModel::stop()
{

}

void AnimAndSoundEffectModel::animation()
{

}

void AnimAndSoundEffectModel::destroy()
{

}
