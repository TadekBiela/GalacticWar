#ifndef BACKGROUNDEFFECTMODEL_HPP
#define BACKGROUNDEFFECTMODEL_HPP

#include "animationeffectmodel.hpp"

enum background_effect
{
    first_element = 0,
    star          = 0,
    star2         = 1,
    star3         = 2,
    comet         = 3,
    last_element  = 3
};

struct BackgroundEffect;

class BackgroundEffectModel : public AnimationEffectModel
{
    Q_OBJECT
public:
    BackgroundEffectModel(background_effect type,
                          QPointF           startPosition,
                          int               moveDirection,
                          QGraphicsScene*   targetScene);
    virtual ~BackgroundEffectModel();
    void play() override;

private slots:
    void move();
    void start() override;
    void stop() override;

private:
    int    m_moveDirection;
    QTimer m_moveTimer;

    static const BackgroundEffect s_backgroundEffectsConfig[background_effect::last_element + 1];
};

#endif // BACKGROUNDEFFECTMODEL_HPP
