
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


#ifndef HEALTHMODEL_HPP
#define HEALTHMODEL_HPP

enum Health_Status
{
    Health_Status_No_More  = 0,
    Health_Status_Still_Is = 1
};

class HealthModel
{
public:
    HealthModel();
    ~HealthModel();
    int getCurrentHealthInPercent() const;
    void add(int healthPoints);
    Health_Status subtract(int healthPoints);

protected:
    int m_currentHealth;
};

#endif // HEALTHMODEL_HPP
