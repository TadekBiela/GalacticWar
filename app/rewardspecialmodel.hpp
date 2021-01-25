
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


#ifndef REWARDSPECIALMODEL_HPP
#define REWARDSPECIALMODEL_HPP

#include "rewardmodel.hpp"
#include "rewardtypes.hpp"
#include <QString>

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
    QString      m_soundName;
};

#endif // REWARDSPECIALMODEL_HPP
