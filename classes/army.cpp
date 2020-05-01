#include <vector>
#include "army.h"


void Army::AddUnit(Unit *unit, size_t line_number, size_t squad_number) {
    lines[line_number][squad_number]->units.push_back(unit);
    unit->SetParent(lines[line_number][squad_number]);
    lifes_sum += unit->health;
}

void Army::AddSquad(size_t line_number) {
    lines[line_number].emplace_back(new Squad(this));
}

void Army::AddLine() {
    lines.emplace_back(0);
}

void Army::Attack(Army *enemy) {
    for (size_t j = 0; j < lines.size(); ++j) {
        for (int i = static_cast<int>(lines[j].size()) - 1; i >= 0; --i) {
            if (!lines[j][i]->units.empty()) lines[j][i]->Attack(enemy);
            else lines[j].erase(lines[j].begin() + i);
        }
    }
}

void Army::Recharge() {
    for (const auto& line : lines) {
        for (auto squad : line) {
            squad->Recharge();
        }
    }
}
