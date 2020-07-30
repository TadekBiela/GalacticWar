#ifndef ANIMATIONEFFECTMODEL_HPP
#define ANIMATIONEFFECTMODEL_HPP

#include "definitions.hpp"
#include "gameobject.hpp"
#include "imagestorage.hpp"
#include <QString>
#include <QPointF>
#include <QImage>
#include <QTimer>

class AnimationEffectModel : public GameObject
{
    Q_OBJECT
public:
    AnimationEffectModel(QString animationName,
                         QPointF position,
                         int     animationFrameWidth,
                         int     animationFrameHeight,
                         int     numOfFrames = def::maxAnimationFrames);
    virtual ~AnimationEffectModel();
    virtual void play();

public slots:
    void start();
    void stop();

protected slots:
    void animation();
    void destroy();

protected:
    QImage* m_image;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
    int     m_animationFrameWidth;
    int     m_animationFrameHeight;
    int     m_numOfFrames;
};

#endif // ANIMATIONEFFECTMODEL_HPP
