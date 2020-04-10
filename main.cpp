#include <iostream>
#include <vector>

int count_of_coins = 1000000;

class Unit{
public:
    int health;
};

class AbstractWarrior : public Unit {
public:
    static const int price = 10;
    int defense = 0;
    int strength;
    int defence_speed;
};
class EnglishWarrior : public AbstractWarrior {
public:
    EnglishWarrior() {
        health = 60;
        strength = 8;
        defence_speed = 2;
    }
};
class FrenchWarrior : public AbstractWarrior {
public:
    FrenchWarrior() {
        health = 50;
        strength = 10;
        defence_speed = 1;
    }
};

class AbstractArcher : public Unit {
public:
    static const int price = 7;
    int long_distance_strength;
    int short_distance_strength;
};
class EnglishArcher : public AbstractArcher {
public:
    EnglishArcher() {
        health = 30;
        long_distance_strength = 6;
        short_distance_strength = 3;
    }
};
class FrenchArcher : public AbstractArcher {
public:
    FrenchArcher() {
        health = 20;
        long_distance_strength = 7;
        short_distance_strength = 4;
    }
};

class AbstractHorseman : public Unit {
public:
    static const int price = 25;
    int strength;
};
class EnglishHorseman : public AbstractHorseman {
public:
    EnglishHorseman() {
        health = 105;
        strength = 2;
    }
};
class FrenchHorseman : public AbstractHorseman {
public:
    FrenchHorseman() {
        health = 90;
        strength = 3;
    }
};

class AbstractFactory {
public:
    virtual AbstractWarrior* CreateWarrior() const = 0;
    virtual AbstractArcher* CreateArcher() const = 0;
    virtual AbstractHorseman* CreateHorseman() const = 0;
};
class EnglishFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior() const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractWarrior::price;
        return new EnglishWarrior();
    }
    AbstractArcher* CreateArcher() const override {
        if (count_of_coins < AbstractArcher::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractArcher::price;
        return new EnglishArcher;
    }
    AbstractHorseman* CreateHorseman() const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractHorseman::price;
        return new EnglishHorseman();
    }
};
class FrenchFactory : public AbstractFactory{
public:
    AbstractWarrior* CreateWarrior() const override {
        if (count_of_coins < AbstractWarrior::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractWarrior::price;
        return new FrenchWarrior();
    }
    AbstractArcher* CreateArcher() const override {
        if (count_of_coins < AbstractArcher::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractArcher::price;
        return new FrenchArcher();
    }
    AbstractHorseman* CreateHorseman() const override {
        if (count_of_coins < AbstractHorseman::price) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return nullptr;
        }
        count_of_coins -= AbstractHorseman::price;
        return new FrenchHorseman();
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
    AbstractFactory* factory;

    Player(int number, int x, int y) {
        current_number = number;
        x_cord = x;
        y_cord = y;
        std::cout << "Creating player" << number << " character : " << std::endl;
        factory = CreateFactory();
        //players.push_back(this);
    }

    void PrintMap() const;
};

void Player::PrintMap() const {
    std::string print_string = "_____   _____   _____   _____   _____";
    print_string[2] = '*';
    std::cout << print_string << std::endl;
}

int main() {
    std::vector<Player*> players;
    Player player(1, 1, 1);
    players.push_back(&player);
    player.PrintMap();

    return 0;
}