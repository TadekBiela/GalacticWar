#ifndef REWARDCONTROLLER_HPP
#define REWARDCONTROLLER_HPP

#include "definitions.hpp"
#include "generalview.hpp"
#include "irandomgenerator.hpp"
#include "rewardtypes.hpp"
#include <QObject>
#include <QGraphicsItem>
#include "QPointF"

class RewardController : public QObject
{
    Q_OBJECT
public:
    RewardController(GeneralView*      view,
                     IRandomGenerator* generator);
    virtual ~RewardController();

signals:
    void addRewardToScene(QGraphicsItem* reward);
    void rewardCoinCollected(coin_type coin);
    void rewardSpecialCollected(special_type special);

public slots:
    void spawnRewards(QPointF position, int tier);
    void coinCollected(coin_type coin);
    void specialCollected(special_type special);

protected:
    IRandomGenerator* m_generator;

    static const int s_minCoinsInTier[def::maxTier];
    static const int s_maxCoinsInTier[def::maxTier];
    static const int s_coinTypeInTier[def::maxTier][10];
    static const int s_specialChanceInTier[def::maxTier];
};

#endif // REWARDCONTROLLER_HPP
