#include "weapons.hpp"

weapon defaultWeapon = { weapon_type::defWeapon, 10, &defaultFireFunc, 300 };

weapon weapons[def::maxWeaponTypes * def::maxWeaponLevel] = {
    { weapon_type::redWeapon,  40, &redLevel1FireFunc, 700 },
    { weapon_type::redWeapon,  50, &redLevel2FireFunc, 650 },
    { weapon_type::redWeapon,  70, &redLevel3FireFunc, 620 },
    { weapon_type::redWeapon, 100, &redLevel4FireFunc, 580 },
    { weapon_type::redWeapon, 150, &redLevel5FireFunc, 500 },

    { weapon_type::yellowWeapon,  30, &yellowLevel1FireFunc, 280 },
    { weapon_type::yellowWeapon,  40, &yellowLevel2FireFunc, 220 },
    { weapon_type::yellowWeapon,  50, &yellowLevel3FireFunc, 160 },
    { weapon_type::yellowWeapon,  80, &yellowLevel4FireFunc, 120 },
    { weapon_type::yellowWeapon, 120, &yellowLevel5FireFunc, 100 },

    { weapon_type::blueWeapon, 12, &blueLevel1FireFunc, 140 },
    { weapon_type::blueWeapon, 12, &blueLevel2FireFunc, 120 },
    { weapon_type::blueWeapon, 15, &blueLevel3FireFunc, 100 },
    { weapon_type::blueWeapon, 20, &blueLevel4FireFunc,  80 },
    { weapon_type::blueWeapon, 30, &blueLevel5FireFunc,  60 }
                                          };
