#pragma once

#include "all_abstract_units.h"
#include "variables_eng.h"


class EnglishArcher : public AbstractArcher {
public:
    explicit EnglishArcher() {
        health = ENG_ARCHER_HEALTH;
        long_dist_strength = ENG_ARCHER_LONG_STR;
        strength = ENG_ARCHER_SHORT_STR;
    }
};

class EnglishHorseman : public AbstractHorseman {
public:
    explicit EnglishHorseman() {
        health = ENG_HORSEMAN_HEALTH;
        strength = ENG_HORSEMAN_STRENGTH;
    }
};

class EnglishWarrior : public AbstractWarrior {
public:
    explicit EnglishWarrior() {
        health = ENG_WARRIOR_HEALTH;
        strength = ENG_WARRIOR_STRENGTH;
        defence_speed = ENG_WARRIOR_DEF_SPEED;
    }
};
