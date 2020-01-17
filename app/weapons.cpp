#include "weapons.hpp"

weapon defaultWeapon = { weapon_type::defWeapon, 10, &defaultFireFunc, 300 };

weapon weapons[def::maxWeaponTypes * def::maxWeaponLevel] = {
    { weapon_type::redWeapon, 20, &redLevel1FireFunc, 200 },
    { weapon_type::redWeapon, 20, &redLevel2FireFunc, 180 },
    { weapon_type::redWeapon, 40, &redLevel3FireFunc, 160 },
    { weapon_type::redWeapon, 60, &redLevel4FireFunc, 140 },
    { weapon_type::redWeapon, 80, &redLevel5FireFunc, 120 },

    { weapon_type::yellowWeapon,  30, &yellowLevel1FireFunc, 300 },
    { weapon_type::yellowWeapon,  40, &yellowLevel2FireFunc, 260 },
    { weapon_type::yellowWeapon,  40, &yellowLevel3FireFunc, 240 },
    { weapon_type::yellowWeapon,  80, &yellowLevel4FireFunc, 200 },
    { weapon_type::yellowWeapon, 120, &yellowLevel5FireFunc, 180 },

    { weapon_type::blueWeapon, 12, &blueLevel1FireFunc, 140 },
    { weapon_type::blueWeapon, 12, &blueLevel2FireFunc, 120 },
    { weapon_type::blueWeapon, 15, &blueLevel3FireFunc, 100 },
    { weapon_type::blueWeapon, 20, &blueLevel4FireFunc,  80 },
    { weapon_type::blueWeapon, 30, &blueLevel5FireFunc,  60 }
                                          };
