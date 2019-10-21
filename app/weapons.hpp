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

extern weapon defaultWeapon;
extern weapon weapons[def::maxWeaponTypes * def::maxWeaponLevel];

#endif // WEAPONS_HPP
