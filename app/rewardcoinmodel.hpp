#ifndef REWARDCOINMODEL_HPP
#define REWARDCOINMODEL_HPP

#include "rewardmodel.hpp"
#include "rewardtypes.hpp"

class RewardCoinModel : public RewardModel
{
    Q_OBJECT
public:
    RewardCoinModel(coin_type type);
    virtual ~RewardCoinModel();
    void      collect();
    coin_type getType() { return m_type; }

signals:
    void collected(coin_type type);

protected:
    coin_type m_type;
};

#endif // REWARDCOINMODEL_HPP
