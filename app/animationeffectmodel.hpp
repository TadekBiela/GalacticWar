#ifndef ANIMATIONEFFECTMODEL_HPP
#define ANIMATIONEFFECTMODEL_HPP

#include "animationplaneview.hpp"
#include "definitions.hpp"
#include "imagestorage.hpp"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include <QPointF>
#include <QImage>
#include <QTimer>

class AnimationEffectModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AnimationEffectModel(QString         animationName,
                         QPointF         position,
                         int             animationFrameWidth,
                         int             animationFrameHeight,
                         int             numOfFrames = def::maxAnimationFrames,
                         QGraphicsScene* targetScene = g_animationPlaneView->scene());
    virtual ~AnimationEffectModel();
    virtual void play();

public slots:
    virtual void start();
    virtual void stop();

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
