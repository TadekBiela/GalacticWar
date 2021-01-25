
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


#include "animationeffectmodel.hpp"
#include "functions.hpp"

AnimationEffectModel::AnimationEffectModel(QString         animationName,
                                           QPointF         position,
                                           int             animationFrameWidth,
                                           int             animationFrameHeight,
                                           int             numOfFrames,
                                           QGraphicsScene* targetScene)
    : m_animationFrameIdx(0),
      m_animationFrameWidth(animationFrameWidth),
      m_animationFrameHeight(animationFrameHeight),
      m_numOfFrames(numOfFrames)
{
    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_animationFrameWidth,
                                m_animationFrameHeight));

    position.setX(position.x() - m_animationFrameWidth  / 2);
    position.setY(position.y() - m_animationFrameHeight / 2);
    setPos(position);

    connect(&m_animationTimer, SIGNAL(timeout()), this, SLOT(animation()));

    m_animationTimer.setInterval(def::animationFrameDuration);

    targetScene->addItem(this);
}

AnimationEffectModel::~AnimationEffectModel()
{

}

void AnimationEffectModel::play()
{
    m_animationTimer.start();
}

void AnimationEffectModel::start()
{
    m_animationTimer.start();
}

void AnimationEffectModel::stop()
{
    m_animationTimer.stop();
}

void AnimationEffectModel::animation()
{
    m_animationFrameIdx++;

    if(m_numOfFrames - 1 < m_animationFrameIdx)
    {
        destroy();
        return;
    }

    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                0,
                                m_animationFrameWidth,
                                m_animationFrameHeight));
}

void AnimationEffectModel::destroy()
{
    QGraphicsScene* scene = QGraphicsItem::scene();
    if(scene)
    {
        scene->removeItem(this);
    }
    delete this;
}
