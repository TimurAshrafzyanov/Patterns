#pragma once

#include <cstddef>


class Squad;
class Army;
class Unit {
public:
    int health;
    int strength;
    Squad *parent_squad = nullptr;

    virtual void Attack(Army *enemy) const;
    virtual void  Recharge();

    virtual void GetInjured(int count_of_lifes, std::size_t self_position);
    void RemoveFromArmy();
    void SetParent(Squad *squad);
};

