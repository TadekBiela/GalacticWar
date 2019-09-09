#ifndef REWARDCOINMODEL_HPP
#define REWARDCOINMODEL_HPP

#include "rewardmodel.hpp"
#include "rewardtypes.hpp"

class RewardCoinModel : public RewardModel
{
public:
    RewardCoinModel(coin_type type);
    void collected();

signals:
    void collected(coin_type type);

public slots:
    void animation();

protected:
    coin_type m_type;
};

#endif // REWARDCOINMODEL_HPP
