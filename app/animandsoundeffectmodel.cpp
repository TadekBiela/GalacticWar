#include "animandsoundeffectmodel.hpp"
#include "definitions.hpp"
#include "functions.hpp"
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>
#include <QGraphicsScene>

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

void AnimAndSoundEffectModel::animationSetup(QString animationName, QPointF position)
{

}

void AnimAndSoundEffectModel::soundSetup(QString soundName)
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
    if(m_isAnimEnabled)
    {
        m_animationTimer.stop();
    }
    if(m_isSoundEnabled)
    {
        m_sound.pause();
    }
    m_remainigDestroyTime = m_destroyTimer.remainingTime();
    m_destroyTimer.stop();
}

void AnimAndSoundEffectModel::animation()
{
    if(++m_animationFrameIdx > def::maxAnimationFrameIdx)
    {
        m_animationFrameIdx = 0;
    }

    setPixmap(getAnimationFrame(m_image, m_animationFrameIdx));
}

void AnimAndSoundEffectModel::destroy()
{
    auto scene = QGraphicsItem::scene();
    if(scene)
    {
        scene->removeItem(this);
    }
    delete this;
}
