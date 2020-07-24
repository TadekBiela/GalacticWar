#include "backgroundeffectmodel.hpp"
#include "functions.hpp"

struct BackgroundEffect
{
    QString name;
    int     animationFrameWidth;
    int     animationFrameHeight;
    int     numOfFrames;
    int     moveTimeDelay;
};

const BackgroundEffect BackgroundEffectModel::s_backgroundEffectsConfig[background_effect::last_element + 1] =
    { { "star", 10, 10, 5, 20 } };

BackgroundEffectModel::BackgroundEffectModel(background_effect type,
                                             QPointF           startPosition,
                                             int               moveDirection)
    : AnimationEffectModel(s_backgroundEffectsConfig[type].name,
                           startPosition,
                           s_backgroundEffectsConfig[type].animationFrameWidth,
                           s_backgroundEffectsConfig[type].animationFrameHeight,
                           s_backgroundEffectsConfig[type].numOfFrames),
      m_moveDirection(moveDirection),
      m_moveTimer()
{
    connect(&m_moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    m_moveTimer.setInterval(s_backgroundEffectsConfig[type].moveTimeDelay);
}

BackgroundEffectModel::~BackgroundEffectModel()
{

}

void BackgroundEffectModel::play()
{
    AnimationEffectModel::play();
    m_moveTimer.start();
}

void BackgroundEffectModel::move()
{
    QPointF newPosition = moveForward(pos(), m_moveDirection);
    this->setPos(newPosition);

    if(isOutOfScene(pos(), pixmap()))
    {
        delete this;
    }
}
