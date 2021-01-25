
/************************************************************************************
** Copyright (C) 2018-2020 Tadeusz Biela (TED)
** Contact: https://www.linkedin.com/in/tadeuszbiela/
**
** This file is part of Galactic War 2D Space Shooter Game.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License version 3.
** The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE included in the packaging of this file.
** Please review the following information to ensure the GNU General Public License
** requirements will be met:  https://www.gnu.org/licenses/gpl-3.0.html.
**
*************************************************************************************/


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
