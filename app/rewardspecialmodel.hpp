#ifndef REWARDSPECIALMODEL_HPP
#define REWARDSPECIALMODEL_HPP

#include "rewardmodel.hpp"
#include "rewardtypes.hpp"

class RewardSpecialModel : public RewardModel
{
    Q_OBJECT
public:
    RewardSpecialModel(special_type type);
    void collect();

signals:
    void collected(special_type type);

public slots:
    void animation();

protected:
    special_type m_type;
};

#endif // REWARDSPECIALMODEL_HPP
