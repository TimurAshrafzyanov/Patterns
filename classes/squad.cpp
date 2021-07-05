#include "squad.h"


void Squad::Attack(Army *enemy) const {
    for (auto unit : units) {
        unit->Attack(enemy);
    }
}
void Squad::Recharge() {
    for (auto unit : units) {
        unit->Recharge();
    }
}
