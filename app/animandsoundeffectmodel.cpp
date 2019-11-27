#include "animandsoundeffectmodel.hpp"
#include "definitions.hpp"
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include <QMediaPlayer>

AnimAndSoundEffectModel::AnimAndSoundEffectModel(bool    isAnim,
                                                 QString animPath,
                                                 QPointF animPos,
                                                 bool    isSound,
                                                 QString soundPath)
                                                  : m_animationFrameIdx(0)
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
