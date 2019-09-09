#ifndef REWARDMODEL_HPP
#define REWARDMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class RewardModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RewardModel();
    ~RewardModel();
    virtual void collect() = 0;

public slots:
    virtual void animation() = 0;
    void destroy();

protected:
    int    m_animationFrameIdx;
    QTimer m_animationTimer;
    QTimer m_destroyTimer;
};

#endif // REWARDMODEL_HPP
