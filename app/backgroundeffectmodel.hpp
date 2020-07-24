#ifndef BACKGROUNDEFFECTMODEL_HPP
#define BACKGROUNDEFFECTMODEL_HPP

#include "animationeffectmodel.hpp"

enum background_effect
{
    star = 0,
    last_element = 0
};

struct BackgroundEffect;

class BackgroundEffectModel : public AnimationEffectModel
{
    Q_OBJECT
public:
    BackgroundEffectModel(background_effect type,
                          QPointF           startPosition,
                          int               moveDirection);
    virtual ~BackgroundEffectModel();
    void play() override;

private slots:
    void move();

private:
    int    m_moveDirection;
    QTimer m_moveTimer;

    static const BackgroundEffect s_backgroundEffectsConfig[background_effect::last_element + 1];
};

#endif // BACKGROUNDEFFECTMODEL_HPP
