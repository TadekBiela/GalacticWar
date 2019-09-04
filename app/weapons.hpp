#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include "definitions.hpp"
#include "firefunctions.hpp"
#include "weapontype.hpp"

struct weapon
{
    weapon_type type;
    int         damage;
    ::fire      fireFuncPtr;
    int         fireTimeDelay;
};

extern const weapon defaultWeapon;
extern const weapon redWeapons[def::maxWeaponLevel];
extern const weapon yellowWeapons[def::maxWeaponLevel];
extern const weapon blueWeapons[def::maxWeaponLevel];

#endif // WEAPONS_HPP
