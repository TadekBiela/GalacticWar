#ifndef REWARDMODEL_HPP
#define REWARDMODEL_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "rewardtype.hpp"

class RewardModel : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RewardModel();
    ~RewardModel();
    void collected();

signals:
    void collected(reward_type type);

public slots:
    virtual void animation() = 0;
    void destroy();

protected:
    reward_type m_type;
    int         m_animationFrameIdx;
    QTimer      m_animationTimer;
    QTimer      m_destroyTimer;
};

#endif // REWARDMODEL_HPP
