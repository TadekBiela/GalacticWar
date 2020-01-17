#include "weapons.hpp"

weapon defaultWeapon = { weapon_type::defWeapon, 10, &defaultFireFunc, 300 };

weapon weapons[def::maxWeaponTypes * def::maxWeaponLevel] = {
    { weapon_type::redWeapon, 20, &redLevel1FireFunc, 20 },
    { weapon_type::redWeapon, 20, &redLevel2FireFunc, 18 },
    { weapon_type::redWeapon, 40, &redLevel3FireFunc, 16 },
    { weapon_type::redWeapon, 60, &redLevel4FireFunc, 14 },
    { weapon_type::redWeapon, 80, &redLevel5FireFunc, 12 },

    { weapon_type::yellowWeapon,  30, &yellowLevel1FireFunc, 30 },
    { weapon_type::yellowWeapon,  40, &yellowLevel2FireFunc, 26 },
    { weapon_type::yellowWeapon,  40, &yellowLevel3FireFunc, 24 },
    { weapon_type::yellowWeapon,  80, &yellowLevel4FireFunc, 20 },
    { weapon_type::yellowWeapon, 120, &yellowLevel5FireFunc, 18 },

    { weapon_type::blueWeapon, 12, &blueLevel1FireFunc, 14 },
    { weapon_type::blueWeapon, 12, &blueLevel2FireFunc, 12 },
    { weapon_type::blueWeapon, 15, &blueLevel3FireFunc, 10 },
    { weapon_type::blueWeapon, 20, &blueLevel4FireFunc,  8 },
    { weapon_type::blueWeapon, 30, &blueLevel5FireFunc,  6 }
                                          };
