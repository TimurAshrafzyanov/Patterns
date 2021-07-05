#pragma once

#include "abstract_factory.h"
#include "../classes/all_french_units.h"



class FrenchFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior() const override {
        return new FrenchWarrior();
    }
    AbstractArcher* CreateArcher() const override {
        return new FrenchArcher();
    }
    AbstractHorseman* CreateHorseman() const override {
        return new FrenchHorseman();
    }
};
