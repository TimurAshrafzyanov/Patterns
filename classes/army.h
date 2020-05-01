#pragma once

#include <vector>
#include "squad.h"


class Army {
public:
    std::vector< std::vector<Squad *> > lines;
    long long lifes_sum = 0;

    template<typename... Squads>
    Army(Squads... squads) {
        lines.emplace_back(0);
        for (auto p : std::initializer_list<Squad *>{squads...}) {
            this->lines[0].push_back(p);
        }
    }

    void AddUnit(Unit *unit, size_t line_number, size_t squad_number);
    void AddSquad(size_t line_number);
    void AddLine();
    void Attack(Army *);
    void Recharge();
};
