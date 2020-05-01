#pragma once

#include "abstract_factory.h"
#include "../classes/all_english_units.h"




class EnglishFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior() const override {
        return new EnglishWarrior();
    }
    AbstractArcher* CreateArcher() const override {
        return new EnglishArcher();
    }
    AbstractHorseman* CreateHorseman() const override {
        return new EnglishHorseman();
    }
};
