#ifndef REWARDCONTROLLER_HPP
#define REWARDCONTROLLER_HPP

#include "generalview.hpp"
#include "irandomgenerator.hpp"
#include "rewardcoinmodel.hpp"
#include "rewardspecialmodel.hpp"
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
    void rewardScpecialCollected(special_type scpecial);

public slots:
    void spawnRewards(QPointF position, int tier);
    void coinCollected(coin_type coin);
    void specialCollected(special_type scpecial);

protected:
    IRandomGenerator* m_generator;
};

#endif // REWARDCONTROLLER_HPP
