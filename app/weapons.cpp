
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


#include "weapons.hpp"

weapon defaultWeapon = { weapon_type::defWeapon, 10, &defaultFireFunc, 300 };

weapon weapons[def::maxWeaponTypes * def::maxWeaponLevel] = {
    { weapon_type::redWeapon,  40, &redLevel1FireFunc, 700 },
    { weapon_type::redWeapon,  50, &redLevel2FireFunc, 650 },
    { weapon_type::redWeapon,  70, &redLevel3FireFunc, 620 },
    { weapon_type::redWeapon, 110, &redLevel4FireFunc, 560 },
    { weapon_type::redWeapon, 140, &redLevel5FireFunc, 500 },

    { weapon_type::yellowWeapon,  30, &yellowLevel1FireFunc, 280 },
    { weapon_type::yellowWeapon,  50, &yellowLevel2FireFunc, 220 },
    { weapon_type::yellowWeapon,  80, &yellowLevel3FireFunc, 160 },
    { weapon_type::yellowWeapon, 140, &yellowLevel4FireFunc, 120 },
    { weapon_type::yellowWeapon, 200, &yellowLevel5FireFunc, 100 },

    { weapon_type::blueWeapon, 12, &blueLevel1FireFunc, 140 },
    { weapon_type::blueWeapon, 20, &blueLevel2FireFunc, 120 },
    { weapon_type::blueWeapon, 25, &blueLevel3FireFunc, 100 },
    { weapon_type::blueWeapon, 35, &blueLevel4FireFunc,  80 },
    { weapon_type::blueWeapon, 45, &blueLevel5FireFunc,  60 }
};
