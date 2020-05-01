#include <iostream>
#include <vector>
#include <random>
#include <typeinfo>
#include <set>
#include <sstream>
#include <fstream>
#include "variables.h"


class Squad;
class Army;

class Unit {
public:
    int health;
    int strength;
    Squad *parent_squad = nullptr;

    virtual void Attack(Army *enemy) const;
    virtual void  Recharge();

    virtual void GetInjured(int count_of_lifes, size_t self_position);
    void RemoveFromArmy();
    void SetParent(Squad *squad);
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




class AbstractWarrior : public Unit {
public:
    static const int price = WARRIOR_PRICE;
    int defense = 0;
    int defence_speed;

    void Recharge() override;
};
void AbstractWarrior::Recharge() {
    defense += defence_speed;
}

class EnglishWarrior : public AbstractWarrior {
public:
    explicit EnglishWarrior() {
        health = ENG_WARRIOR_HEALTH;
        strength = ENG_WARRIOR_STRENGTH;
        defence_speed = ENG_WARRIOR_DEF_SPEED;
    }
};
class FrenchWarrior : public AbstractWarrior {
public:
    explicit FrenchWarrior() {
        health = FR_WARRIOR_HEALTH;
        strength = FR_WARRIOR_STRENGTH;
        defence_speed = FR_WARRIOR_DEF_SPEED;
    }
};

class AbstractArcher : public Unit {
public:
    static const int price = ARCHER_PRICE;
    int long_dist_strength;

    //void Attack(Army *) const override;
};
//void AbstractArcher::Attack(Army *) const {}

class EnglishArcher : public AbstractArcher {
public:
    explicit EnglishArcher() {
        health = ENG_ARCHER_HEALTH;
        long_dist_strength = ENG_ARCHER_LONG_STR;
        strength = ENG_ARCHER_SHORT_STR;
    }
};
class FrenchArcher : public AbstractArcher {
public:
    explicit FrenchArcher() {
        health = FR_ARCHER_HEALTH;
        long_dist_strength = FR_ARCHER_LONG_STR;
        strength = FR_ARCHER_SHORT_STR;
    }
};

class AbstractHorseman : public Unit {
public:
    static const int price = HORSEMAN_PRICE;
};

class EnglishHorseman : public AbstractHorseman {
public:
    explicit EnglishHorseman() {
        health = ENG_HORSEMAN_HEALTH;
        strength = ENG_HORSEMAN_STRENGTH;
    }
};
class FrenchHorseman : public AbstractHorseman {
public:
    explicit FrenchHorseman() {
        health = FR_HORSEMAN_HEALTH;
        strength = FR_HORSEMAN_STRENGTH;
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
        return new EnglishWarrior();
    }
    AbstractArcher* CreateArcher() const override {
        return new EnglishArcher();
    }
    AbstractHorseman* CreateHorseman() const override {
        return new EnglishHorseman();
    }
};

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

AbstractFactory* CreateFactory() {
    std::string your_fraction;
    std::cout << "Please choose tour fraction : England/France (E/F)" << std::endl;
    std::cin >> your_fraction;
    while (true) {
        if (your_fraction == "England" || your_fraction == "E") {
            std::cout << "You are playing for England \n" << std::endl;
            return new EnglishFactory();
        } else if (your_fraction == "France" || your_fraction == "F") {
            std::cout << "You are playing for France \n" << std::endl;
            return new FrenchFactory();
        }
        std::cout << "Incorrect format, please choose tour fraction : England/France (E/F)" << std::endl;
        std::cin >> your_fraction;
    }
}





class Player{
public:
    int x_cord;
    int y_cord;
    AbstractFactory *factory;
    Army *army;
    int count_of_coins = 0;
    int coins_speed = START_COINS_SPEED;

    int steps_to_progress;
    bool last_step_attacked = false;

    Player(int number, int x, int y) : steps_to_progress(0) {
        x_cord = x;
        y_cord = y;
        std::cout << "@@@@ Creating " << number << " player`s";
        std::cout << " character @@@@" << std::endl;
        factory = CreateFactory();
        army = new Army();
        army->AddSquad(0);
        Unit *unit = factory->CreateWarrior();
        army->AddUnit(unit, 0, 0);
    }

    void PrintMap(const std::vector<Player *> &players) const;
    void PrintArmy() const;
    bool BuyUnit(char type, size_t line_number, size_t squad_number);
    void Update(bool attacked);
    bool Move(const std::string& direction, std::vector<Player *> &players);
    bool Attack(std::vector<Player *> &players);
    void Recharge();
    void Progress(bool &step);
};

bool Player::BuyUnit(char type, size_t line_number, size_t squad_number) {
    if (type == 'w') {
        if (count_of_coins < WARRIOR_PRICE) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return false;
        } else {
            count_of_coins -= WARRIOR_PRICE;
            army->AddUnit(factory->CreateWarrior(), line_number, squad_number);
        }
    } else if (type == 'a') {
        if (count_of_coins < ARCHER_PRICE) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return false;
        } else {
            count_of_coins -= ARCHER_PRICE;
            army->AddUnit(factory->CreateArcher(), line_number, squad_number);
        }
    } else if (type == 'h') {
        if (count_of_coins < HORSEMAN_PRICE) {
            std::cout << "You haven`t got money fo this" << std::endl;
            return false;
        } else {
            count_of_coins -= HORSEMAN_PRICE;
            army->AddUnit(factory->CreateHorseman(), line_number, squad_number);
        }
    } else return false;
    return true;
}

void Player::Update(bool attacked) {
    count_of_coins += coins_speed;
    if (steps_to_progress > 0) steps_to_progress -= 1;
    last_step_attacked = attacked;

    for (int i = static_cast<int>(army->lines.size()) - 1; i >= 0; --i) {
        std::vector<Squad *> line = army->lines[i];
        if (line.empty() || (line.size() == 1 && line[0]->units.empty())) {
            if (line.size() == 1) delete(line[0]);
            army->lines.erase(army->lines.begin() + i);
        }
    }
}

void Player::PrintMap(const std::vector<Player *> &players) const {
    std::vector<std::string> map(5, "_____   _____   _____   _____   _____");
    std::vector<char> symbols = {'1', '2'};
    for (size_t i = 0; i < players.size(); ++i) {
        map[players[i]->y_cord][2 + players[i]->x_cord * 8] = symbols[i];
    }
    map[y_cord][2 + x_cord * 8] = '*';
    std::cout << "Map : " << std::endl;
    for (const auto& str : map) {
        std::cout << str << std::endl;
    }
}

void Player::PrintArmy() const {
    std::cout << "Army :" << std::endl;
    for (size_t i = 0; i < army->lines.size(); ++i) {
        std::cout << "line " << i << " : " << std::endl;
        for (size_t j = 0; j < army->lines[i].size(); ++j) {
            std::cout << "\tsquad " << j << " : " << std::endl;
            for (size_t k = 0; k < army->lines[i][j]->units.size(); ++k) {
                Unit *unit = army->lines[i][j]->units[k];
                std::cout << "\t\tunit " << k << " : " << std::endl;
                std::cout << "\t\t\tname : " << typeid(*unit).name() << std::endl;
                std::cout << "\t\t\thealth : " << unit->health << std::endl;
            }
        }
    }
}

bool Player::Move(const std::string& direction, std::vector<Player *> &players) {
    bool is_correct = true;
    int new_x = x_cord;
    int new_y = y_cord;

    if (direction == "left") {
        if (x_cord == 0) is_correct = false;
        else new_x -= 1;
    } else if (direction == "right") {
        if (x_cord == 4) is_correct = false;
        else new_x += 1;
    } else if (direction == "up") {
        if (y_cord == 0) is_correct = false;
        else new_y -= 1;
    } else if (direction == "down") {
        if (y_cord == 4) is_correct = false;
        else new_y += 1;
    }
    if (!is_correct) {
        std::cout << "Out of field, choose another direction" << std::endl;
    }

    Player *enemy;
    if (players[0] == this) enemy = players[1];
    else enemy = players[0];
    if (new_x == enemy->x_cord && new_y == enemy->y_cord) {
        is_correct = false;
        std::cout << "This place is occupied" << std::endl;
    } else {
        x_cord = new_x;
        y_cord = new_y;
    }

    return is_correct;
}

bool Player::Attack(std::vector<Player *> &players) {
    Player *enemy;
    if (players[0] == this) enemy = players[1];
    else enemy = players[0];
    if (std::abs(x_cord - enemy->x_cord) + std::abs(y_cord - enemy->y_cord) <= 1) {
        army->Attack(enemy->army);
        return true;
    } else {
        std::cout << "Enemy is too far to attack" << std::endl;
        return false;
    }
}

void Player::Recharge() {
    army->Recharge();
    count_of_coins += coins_speed;
}

void Player::Progress(bool &step) {
    if (last_step_attacked || steps_to_progress > 0) {
        std::cout << "You can`t progress now" << std::endl;
        return;
    }
    coins_speed += START_COINS_SPEED;
    step = false;
}



void CommandGo(Player *player, bool &step, std::vector<Player *> &players) {
    std::string command;
    std::cin >> command;
    std::set<std::string> str;
    str.insert("left");
    str.insert("right");
    str.insert("up");
    str.insert("down");
    if (!str.count(command))
        std::cout << "Wrong direction" << std::endl;
    else if (player->Move(command, players)) step = false;
}


void CommandNew(Player *player, bool &step) {
    std::string command;
    std::cin >> command;
    if (command == "line") {
        player->army->AddLine();
        std::cout << "New line successfully added" << std::endl;
        return;
    }
    if (command == "squad") {
        std::cin >> command;
        std::stringstream s;
        s << command;
        long line;
        s >> line;
        if (!s || line >= player->army->lines.size())
            std::cout << "Wrong line`s number" << std::endl;
        else {
            player->army->AddSquad(line);
            std::cout << "New squad successfully added" << std::endl;
        }
        return;
    }
    if (command == "unit") {
        std::cin >> command;
        std::set<std::string> str;
        str.insert("w");
        str.insert("a");
        str.insert("h");
        if (!str.count(command)) {
            std::cout << "Wrong unit`s name" << std::endl;
            return;
        }
        char type = command[0];

        std::vector<int> cords(2);
        for (size_t i = 0; i < 2; ++i) {
            std::cin >> command;
            std::stringstream s;
            s << command;
            s >> cords[i];
            if (!s) {
                std::cout << "Wrong format" << std::endl;
                return;
            }
        }
        int line = cords[0];
        int squad = cords[1];

        if (line >= player->army->lines.size() || squad >= player->army->lines[line].size()) {
            std::cout << "Wrong line`s or squad`s number" << std::endl;
            return;
        }
        if (player->BuyUnit(type, line, squad)) {
            step = false;
            std::cout << "New unit successfully added" << std::endl;
        }
        return;
    }
    std::cout << "Wrong command with new" << std::endl;
}

void CommandMove(Player *player, bool &step) {
    std::vector<int> cords(5);
    std::string command;
    for(size_t i = 0; i < 5; ++i) {
        std::cin >> command;
        std::stringstream s;
        s << command;
        long number;
        s >> number;
        if (!s) {
            std::cout << "Wrong format" << std::endl;
            return;
        }
        else cords[i] = number;
    }
    if (cords[0] >= player->army->lines.size()
        || cords[3] >= player->army->lines.size()) {
        std::cout << "Wrong line`s number";
        return;
    }
    if (cords[1] >= player->army->lines[cords[0]].size()
        || cords[4] >= player->army->lines[cords[1]].size()) {
        std::cout << "Wrong squad`s number";
        return;
    }
    if (cords[2] >= player->army->lines[cords[0]][cords[1]]->units.size()) {
        std::cout << "Wrong unit`s number";
        return;
    }
    Unit *unit = player->army->lines[cords[0]][cords[1]]->units[cords[2]];
    unit->RemoveFromArmy();
    player->army->AddUnit(unit, cords[3], cords[4]);
    step = false;
}


void GameStep(Player *player, std::vector<Player *> &players) {
    bool step = true;
    bool attacked = false;
    std::string command;
    while (step) {
        std::cin >> command;
        if (command == "map") {
            player->PrintMap(players);
            continue;
        }
        if (command == "army") {
            player->PrintArmy();
            continue;
        }
        if (command == "help") {
            std::string line;
            std::ifstream fs;
            fs.open("help/help.txt");
            while (getline(fs,line)) {
                std::cout << line << std::endl;
            }
            fs.close();
            continue;
        }
        if (command == "balance") {
            std::cout << "Your balance is "
                << player->count_of_coins << " coins" << std::endl;
            continue;
        }
        if (command == "go") {
            CommandGo(player, step, players);
            continue;
        }
        if (command == "attack") {
            if (player->Attack(players)) {
                attacked = true;
                step = false;
            }
            continue;
        }
        if (command == "recharge") {
            player->Recharge();
            step = false;
            continue;
        }
        if (command == "new") {
            CommandNew(player, step);
            continue;
        }
        if (command == "move") {
            CommandMove(player, step);
            continue;
        }
        if (command == "progress") {
            player->Progress(step);
            continue;
        }
        std::cout << "Wrong command" << std::endl;
    }
    player->Update(attacked);
}


int main() {
    std::vector<Player *> players;
    Player player1(1, 0, 0);
    players.push_back(&player1);
    Player player2(2, 0, 1);
    players.push_back(&player2);

    int current_player = 0;
    while (player1.army->lifes_sum > 0 && player2.army->lifes_sum > 0) {
        std::cout << std::endl << "@@@@ Now " << current_player + 1
            << " player`s tern @@@@ \n" << std::endl;
        GameStep(players[current_player], players);
        current_player = 1 - current_player;
    }

    if (player1.army->lifes_sum > 0) current_player = 1;
    else current_player = 2;
    std::cout << std::endl << "@@@@ " << current_player
        << " player won @@@@" << std::endl << "His ";
    players[current_player - 1]->PrintArmy();

    return 0;
}