#pragma once

#include "../classes/all_abstract_units.h"


class AbstractFactory {
public:
    virtual AbstractWarrior* CreateWarrior() const = 0;
    virtual AbstractArcher* CreateArcher() const = 0;
    virtual AbstractHorseman* CreateHorseman() const = 0;
};
