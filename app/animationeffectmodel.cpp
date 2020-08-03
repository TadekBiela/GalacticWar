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
