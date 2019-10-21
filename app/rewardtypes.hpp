#ifndef REWARDTYPES_HPP
#define REWARDTYPES_HPP

#include "definitions.hpp"

enum coin_type
{
    bronze = 0,
    silver,
    gold
};

enum special_type
{
    health = 1,
    weaponRed,
    weaponYellow,
    weaponBlue = def::maxNumOfSpecialRewards
};

#endif // REWARDTYPES_HPP
