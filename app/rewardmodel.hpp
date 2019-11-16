#ifndef REWARDMODEL_HPP
#define REWARDMODEL_HPP

#include "gameobject.hpp"
#include <QTimer>
#include <QImage>
#include <QPixmap>

class RewardModel : public GameObject
{
    Q_OBJECT
public:
    RewardModel();
    virtual ~RewardModel();
    virtual void collect() = 0;

public slots:
    virtual void start();
    virtual void stop();
    virtual void animation();
    void destroy();

protected:
    QPixmap getAnimationFrame();

    QImage m_image;
    int    m_animationFrameIdx;
    QTimer m_animationTimer;
    QTimer m_destroyTimer;
};

#endif // REWARDMODEL_HPP
