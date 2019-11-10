#ifndef REWARDSPECIALMODEL_HPP
#define REWARDSPECIALMODEL_HPP

#include "rewardmodel.hpp"
#include "rewardtypes.hpp"

class RewardSpecialModel : public RewardModel
{
    Q_OBJECT
public:
    RewardSpecialModel(special_type type);
    virtual ~RewardSpecialModel();
    void         collect();
    special_type getType() { return m_type; }

signals:
    void collected(special_type type);

protected:
    special_type m_type;
};

#endif // REWARDSPECIALMODEL_HPP
