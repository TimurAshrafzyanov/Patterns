#include <iostream>
#include <vector>
#include <random>
int count_of_coins = 1000000;

class Squad;
class Army;



class Unit {
public:
    int health;
    Squad *parent_squad;

    virtual void Attack(Army *) const = 0;
    virtual void  Recharge();

    virtual void GetInjured(int count_of_lifes, size_t self_position);
    virtual ~Unit() = 0;
};




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


class Army {
public:
    std::vector< std::vector<Squad *> > lines;

    template<typename... Squads>
    Army(Squads... squads) {
        lines.emplace_back(0);
        for (auto p : std::initializer_list<Squad *>{squads...}) {
            this->lines[0].push_back(p);
        }
    }

    void Attack(Army *) const;
    void Recharge();
};

void Army::Attack(Army *enemy) const {
    for (auto line : lines) {
        for (int i = static_cast<int>(line.size()) - 1; i >= 0; ++i) {
            if (!line[i]->units.empty()) line[i]->Attack(enemy);
            else line.erase(line.begin() + i);
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


void Unit::GetInjured(int count_of_lifes, size_t self_position) {
    health -= count_of_lifes;
    if (health <= 0) {
        parent_squad->units.erase(parent_squad->units.begin() + self_position);
        delete(this);
    }
}
void Unit::Recharge() {}




class AbstractWarrior : public Unit {
protected:
    AbstractWarrior() = default;
public:
    static const int price = 10;
    int defense = 0;
    int strength;
    int defence_speed;

    void Attack(Army *) const override;
    void Recharge() override;
};
void AbstractWarrior::Attack(Army *enemy) const {
    size_t direct_squad = rand() % enemy->lines[0].size();
    size_t direct_unit = rand() % enemy->lines[0][direct_squad]->units.size();
    enemy->lines[0][direct_squad]->units[direct_unit]->GetInjured(strength, direct_unit);
}
void AbstractWarrior::Recharge() {
    defense += defence_speed;
}

class EnglishWarrior : public AbstractWarrior {
public:
    EnglishWarrior(Squad *parent) {
        parent_squad = parent;
        health = 60;
        strength = 8;
        defence_speed = 2;
    }
};
class FrenchWarrior : public AbstractWarrior {
public:
    FrenchWarrior(Squad *parent) {
        parent_squad = parent;
        health = 50;
        strength = 10;
        defence_speed = 1;
    }
};

class AbstractArcher : public Unit {
protected:
    AbstractArcher() = default;
public:
    static const int price = 7;
    int long_distance_strength;
    int short_distance_strength;

    void Attack(Army *) const override;
};
void AbstractArcher::Attack(Army *enemy) const {
    size_t direct_squad = rand() % enemy->lines[0].size();
    size_t direct_unit = rand() % enemy->lines[0][direct_squad]->units.size();
    enemy->lines[0][direct_squad]->units[direct_unit]->GetInjured(short_distance_strength, direct_unit);
}

class EnglishArcher : public AbstractArcher {
public:
    EnglishArcher(Squad *parent) {
        parent_squad = parent;
        health = 30;
        long_distance_strength = 6;
        short_distance_strength = 3;
    }
};
class FrenchArcher : public AbstractArcher {
public:
    FrenchArcher(Squad *parent) {
        parent_squad = parent;
        health = 20;
        long_distance_strength = 7;
        short_distance_strength = 4;
    }
};

class AbstractHorseman : public Unit {
protected:
    AbstractHorseman() = default;
public:
    static const int price = 25;
    int strength;

    void Attack(Army *) const override;
};
void AbstractHorseman::Attack(Army *enemy) const {
    size_t direct_squad = rand() % enemy->lines[0].size();
    size_t direct_unit = rand() % enemy->lines[0][direct_squad]->units.size();
    enemy->lines[0][direct_squad]->units[direct_unit]->GetInjured(strength, direct_unit);
}

class EnglishHorseman : public AbstractHorseman {
public:
    EnglishHorseman(Squad *parent) {
        parent_squad = parent;
        health = 105;
        strength = 2;
    }
};
class FrenchHorseman : public AbstractHorseman {
public:
    FrenchHorseman(Squad *parent) {
        parent_squad = parent;
        health = 90;
        strength = 3;
    }
};



class AbstractFactory {
public:
    virtual AbstractWarrior* CreateWarrior(Squad *squad) const = 0;
    virtual AbstractArcher* CreateArcher(Squad *squad) const = 0;
    virtual AbstractHorseman* CreateHorseman(Squad *squad) const = 0;
};
class EnglishFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior(Squad *squad) const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractWarrior::price;
        return new EnglishWarrior(squad);
    }
    AbstractArcher* CreateArcher(Squad *squad) const override {
        if (count_of_coins < AbstractArcher::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractArcher::price;
        return new EnglishArcher(squad);
    }
    AbstractHorseman* CreateHorseman(Squad *squad) const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractHorseman::price;
        return new EnglishHorseman(squad);
    }
};
class FrenchFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior(Squad *squad) const override {
        if (count_of_coins < AbstractWarrior::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractWarrior::price;
        return new FrenchWarrior(squad);
    }
    AbstractArcher* CreateArcher(Squad *squad) const override {
        if (count_of_coins < AbstractArcher::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractArcher::price;
        return new FrenchArcher(squad);
    }
    AbstractHorseman* CreateHorseman(Squad *squad) const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractHorseman::price;
        return new FrenchHorseman(squad);
    }
};

AbstractFactory* CreateFactory() {
    std::string your_fraction;
    std::cout << "Please choose tour fraction : England/France (E/F)" << std::endl;
    std::cin >> your_fraction;
    while (true) {
        if (your_fraction == "England" || your_fraction == "E") {
            std::cout << "You are playing for England" << std::endl;
            return new EnglishFactory();
        } else if (your_fraction == "France" || your_fraction == "F") {
            std::cout << "You are playing for France" << std::endl;
            return new FrenchFactory();
        }
        std::cout << "Incorrect format, please choose tour fraction : England/France (E/F)" << std::endl;
        std::cin >> your_fraction;
    }
}

class Player{
public:
    int current_number;
    int x_cord;
    int y_cord;
    AbstractFactory *factory;
    Army *army;

    Player(int number, int x, int y) {
        current_number = number;
        x_cord = x;
        y_cord = y;
        std::cout << "Creating player" << number << " character : " << std::endl;
        factory = CreateFactory();
        army = new Army();
    }

    void PrintMap() const;
    void PrintArmy() const;
};

std::vector<Player*> players;

void Player::PrintMap() const {
    std::vector<std::string> map(5, "_____   _____   _____   _____   _____");
    std::vector<char> symbols = {'1', '2'};
    for (size_t i = 0; i < players.size(); ++i) {
        map[players[i]->x_cord][2 + players[i]->y_cord * 8] = symbols[i];
    }
    map[x_cord][2 + y_cord * 8] = '*';
    std::cout << "Map : " << std::endl;
    for (const auto& str : map) {
        std::cout << str << std::endl;
    }
}

void Player::PrintArmy() const {
    for (size_t i = 0; i < army->lines.size(); ++i) {
        std::cout << "line " << i << " : " << std::endl;
        for (size_t j = 0; j < army->lines[i].size(); ++j) {
            std::cout << "\tsquad " << j << " : " << std::endl;
            for (size_t k = 0; k < army->lines[i][j]->units.size(); ++k) {
                Unit *unit = army->lines[i][j]->units[k];
                std::cout << "\t\tunit " << k << " : ";
                std::cout << unit->health << std::endl;
            }
        }
    }
}

int main() {

    Player player(1, 0, 0);
    players.push_back(&player);
    Player player1(2, 4, 4);
    players.push_back(&player1);
    player.PrintMap();
    player1.PrintMap();

    return 0;
}