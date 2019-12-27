#ifndef ANIMATIONEFFECTMODEL_HPP
#define ANIMATIONEFFECTMODEL_HPP

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
    AnimationEffectModel(QGraphicsScene* scene,
                         QString         animationName,
                         QPointF         position);
    virtual ~AnimationEffectModel();

public slots:
    void start(){}
    void stop(){}
    void animation();
    void destroy();

protected:
    QImage* m_image;
    int     m_animationFrameIdx;
    QTimer  m_animationTimer;
};

#endif // ANIMATIONEFFECTMODEL_HPP
