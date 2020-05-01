#include <vector>
#include <random>
#include "army.h"


void Unit::GetInjured(int count_of_lifes, size_t self_position) {
    health -= count_of_lifes;
    parent_squad->parent_army->lifes_sum -= count_of_lifes;
    if (health <= 0) {
        parent_squad->parent_army->lifes_sum -= health;
        parent_squad->units.erase(parent_squad->units.begin() + self_position);
        delete(this);
    }
}

void Unit::Attack(Army *enemy) const {
    size_t direct_squad = rand() % enemy->lines[0].size();
    if (enemy->lines[0][direct_squad]->units.size() != 0) {
        size_t direct_unit = rand() % enemy->lines[0][direct_squad]->units.size();
        enemy->lines[0][direct_squad]->units[direct_unit]->GetInjured(strength, direct_unit);
    }
}

void Unit::Recharge() {}

void Unit::RemoveFromArmy() {
    if (parent_squad != nullptr) {
        size_t i = 0;
        while (parent_squad->units[i] != this) ++i;
        parent_squad->units.erase(parent_squad->units.begin() + i);
        parent_squad->parent_army->lifes_sum -= health;

        if (parent_squad->units.empty()) {
            Army *army = parent_squad->parent_army;
            i = 0;
            size_t j = 0;
            while (army->lines[i][j] != parent_squad) {
                if (j == army->lines[i].size() - 1) {
                    ++i;
                    j = 0;
                } else ++j;
            }
            army->lines[i].erase(army->lines[i].begin() + j);
            delete(parent_squad);
        }

        parent_squad = nullptr;
    }
}

void Unit::SetParent(Squad *squad) {
    parent_squad = squad;
}

