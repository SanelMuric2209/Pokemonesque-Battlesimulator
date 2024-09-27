#pragma once
#include "stats.hpp"
#include <vector>
using std::vector, std::istream, std::string, std::to_string;

class Attack;
class Pokemon {
    string name;
    int level;

    friend Attack;
protected:
    vector<Attack*> moves;
    vector<int> strategy;
private:
    int currentMove;
public:
    bool asleep;
    bool stunned;
    Stat hp;
    Stat atk;
    Stat def;

    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p);
public:
    // Pokemon(const Pokemon& other);
    Pokemon(const Pokemon& other) = delete;
    Pokemon(const string& name, int level);
    virtual ~Pokemon(); 
    static void infos();

    bool isKO() const;
    void rest();
    void restart();
    void levelUp();

    bool attack(Pokemon& other);
    bool fightWith(Pokemon& other);

    bool readStrategy(istream& input);
    virtual void setup() = 0;
    static int number;
};


class Ronflex : public Pokemon {
public:
    Ronflex(int level);
    void setup() override;
};

class Dracofeu : public Pokemon {
public:
    Dracofeu(int level);
    void setup() override;
};

class Florizarre : public Pokemon {
public:
    Florizarre(int level);
    void setup() override;
};

class Tortank : public Pokemon {
public:
    Tortank(int level);
    void setup() override;
};
