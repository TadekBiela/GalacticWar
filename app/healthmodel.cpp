
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


#include "healthmodel.hpp"
#include "definitions.hpp"

HealthModel::HealthModel()
    : m_currentHealth(def::maxPlayerHealth)
{

}

HealthModel::~HealthModel()
{

}

int HealthModel::getCurrentHealthInPercent() const
{
    return m_currentHealth * 100 / def::maxPlayerHealth;
}

void HealthModel::add(int healthPoints)
{
    m_currentHealth += healthPoints;
    if(def::maxPlayerHealth < m_currentHealth)
    {
        m_currentHealth = def::maxPlayerHealth;
    }
}

Health_Status HealthModel::subtract(int healthPoints)
{
    m_currentHealth -= healthPoints;
    if(0 >= m_currentHealth)
    {
        m_currentHealth = 0;
        return Health_Status_No_More;
    }
    return Health_Status_Still_Is;
}
