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
    { { "star",  32, 32, 20, 20 },
      { "star2", 32, 32, 10, 20 },
      { "star3", 32, 32,  5, 15 }};

BackgroundEffectModel::BackgroundEffectModel(background_effect type,
                                             QPointF           startPosition,
                                             int               moveDirection,
                                             QGraphicsScene*   targetScene)
    : AnimationEffectModel(s_backgroundEffectsConfig[type].name,
                           startPosition,
                           s_backgroundEffectsConfig[type].animationFrameWidth,
                           s_backgroundEffectsConfig[type].animationFrameHeight,
                           s_backgroundEffectsConfig[type].numOfFrames,
                           targetScene),
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
