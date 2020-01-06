#include "animationeffectmodel.hpp"
#include "functions.hpp"
#include <QGraphicsScene>

AnimationEffectModel::AnimationEffectModel(QGraphicsScene* scene,
                                           QString         animationName,
                                           QPointF         position,
                                           int             animationFrameWidth,
                                           int             animationFrameHeight,
                                           int             numOfFrames)
                                            : m_animationFrameIdx(0),
                                              m_animationFrameWidth(animationFrameWidth),
                                              m_animationFrameHeight(animationFrameHeight),
                                              m_numOfFrames(numOfFrames)
{
    m_image = g_imageStorage->getImage(animationName);
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
                                m_animationFrameWidth,
                                m_animationFrameHeight));

    position.setX(position.x() - m_animationFrameWidth  / 2);
    position.setY(position.y() - m_animationFrameHeight / 2);
    setPos(position);

    connect(&m_animationTimer, SIGNAL(timeout()), this, SLOT(animation()));

    m_animationTimer.setInterval(def::animationFrameDuration);
    m_animationTimer.start();

    scene->addItem(this);
}

AnimationEffectModel::~AnimationEffectModel()
{

}

void AnimationEffectModel::animation()
{
    if(++m_animationFrameIdx >= m_numOfFrames - 1)
    {
        destroy();
        return;
    }
    setPixmap(getAnimationFrame(m_image,
                                m_animationFrameIdx,
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
