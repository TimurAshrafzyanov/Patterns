#pragma once

#include "all_abstract_units.h"
#include "variables_fr.h"


class FrenchArcher : public AbstractArcher {
public:
    explicit FrenchArcher() {
        health = FR_ARCHER_HEALTH;
        long_dist_strength = FR_ARCHER_LONG_STR;
        strength = FR_ARCHER_SHORT_STR;
    }
};

class FrenchHorseman : public AbstractHorseman {
public:
    explicit FrenchHorseman() {
        health = FR_HORSEMAN_HEALTH;
        strength = FR_HORSEMAN_STRENGTH;
    }
};

class FrenchWarrior : public AbstractWarrior {
public:
    explicit FrenchWarrior() {
        health = FR_WARRIOR_HEALTH;
        strength = FR_WARRIOR_STRENGTH;
        defence_speed = FR_WARRIOR_DEF_SPEED;
    }
};

