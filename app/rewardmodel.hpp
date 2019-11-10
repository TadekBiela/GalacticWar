#ifndef REWARDMODEL_HPP
#define REWARDMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QImage>
#include <QPixmap>

class RewardModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RewardModel();
    virtual ~RewardModel();
    virtual void collect() = 0;

public slots:
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
