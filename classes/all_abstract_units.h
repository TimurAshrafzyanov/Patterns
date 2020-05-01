#pragma once

#include "unit.h"


class AbstractArcher : public Unit {
public:
    int long_dist_strength;
};


class AbstractHorseman : public Unit {};


class AbstractWarrior : public Unit {
public:
    int defense = 0;
    int defence_speed;

    void Recharge() override;
};
