
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


#ifndef IRANDOMGENERATOR_HPP
#define IRANDOMGENERATOR_HPP

class IRandomGenerator
{
public:
    IRandomGenerator() {}
    virtual ~IRandomGenerator() {}
    virtual int bounded(int lowest, int highest) = 0;
};

#endif // IRANDOMGENERATOR_HPP
