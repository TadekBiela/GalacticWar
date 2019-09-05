#include "weapons.hpp"

weapon defaultWeapon = { weapon_type::defWeapon, 1, &defaultFireFunc, 20 };

weapon weapons[3 * def::maxWeaponLevel] = {
    { weapon_type::redWeapon, 2, &redLevel1FireFunc, 20 },
    { weapon_type::redWeapon, 2, &redLevel2FireFunc, 18 },
    { weapon_type::redWeapon, 4, &redLevel3FireFunc, 16 },
    { weapon_type::redWeapon, 6, &redLevel4FireFunc, 14 },
    { weapon_type::redWeapon, 8, &redLevel5FireFunc, 12 },

    { weapon_type::yellowWeapon,  3, &yellowLevel1FireFunc, 30 },
    { weapon_type::yellowWeapon,  4, &yellowLevel2FireFunc, 26 },
    { weapon_type::yellowWeapon,  4, &yellowLevel3FireFunc, 24 },
    { weapon_type::yellowWeapon,  8, &yellowLevel4FireFunc, 20 },
    { weapon_type::yellowWeapon, 12, &yellowLevel5FireFunc, 18 },

    { weapon_type::blueWeapon, 1, &blueLevel1FireFunc, 14 },
    { weapon_type::blueWeapon, 1, &blueLevel2FireFunc, 12 },
    { weapon_type::blueWeapon, 1, &blueLevel3FireFunc, 10 },
    { weapon_type::blueWeapon, 2, &blueLevel4FireFunc,  8 },
    { weapon_type::blueWeapon, 3, &blueLevel5FireFunc,  6 }
                                          };
