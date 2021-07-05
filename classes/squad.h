#pragma once

#include <vector>
#include "unit.h"


class Squad {
public:
    std::vector<Unit *> units;
    Army *parent_army;

    template<typename... Units>
    Squad(Army *parent, Units... units) {
        parent_army = parent;
        for (auto p : std::initializer_list<Unit *>{units...}) {
            this->units.push_back(p);
        }
    }

    void Attack(Army *) const;
    void Recharge();
};
