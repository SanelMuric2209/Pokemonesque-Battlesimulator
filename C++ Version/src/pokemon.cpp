#include <sstream>
#include "../include/pokemon.hpp"
#include "attack.hpp"
#include <stdexcept>

Pokemon::Pokemon(const std::string& name, int level)
    : name(name), level(level), currentMove(0), asleep(false),
      stunned(false), hp(Stat(true)), atk(Stat(false)), def(Stat(false)) {
        Pokemon::number++;
      }

bool Pokemon::isKO() const {
    return hp.current <= 0;
}

void Pokemon::rest() {
    hp.reset();
    atk.reset();
    def.reset();
    asleep = false;
    stunned = false;
    currentMove = 0;
}

void Pokemon::restart() {
    atk.reset();
    def.reset();
    asleep = false;
    stunned = false;
    currentMove = 0;
}

void Pokemon::levelUp() {
    ++hp;
    ++atk;
    ++def;
    ++level;
}

bool Pokemon::attack(Pokemon& other) {
    if (isKO() || other.isKO()) return false;

    if (asleep) {
        asleep = false;
        return false;
    }

    moves.at(strategy.at(currentMove))->execute(*this, other);
    currentMove = (currentMove + 1) % strategy.size();
    return true;
}

bool Pokemon::fightWith(Pokemon& other) {
    int round = 0;
    while (round < 200 && !isKO() && !other.isKO()) {
        attack(other);
        other.attack(*this);
        round++;
    }
    return !isKO();
}

bool isInt(const std::string& s) { // i wrote this myself with gpt
    if (s.empty()) return false;

    size_t start = 0;
    // Allow a leading '+' or '-'
    if (s[0] == '+' || s[0] == '-') {
        if (s.size() == 1) return false;  // a single '+' or '-' is not an integer
        start = 1;
    }

    // Check if all remaining characters are digits
    for (size_t i = start; i < s.size(); ++i) {
        if (!std::isdigit(s[i])) {
            return false;
        }
    }

    return true;
}

bool Pokemon::readStrategy(std::istream& input) {
    strategy.resize(3);
    std::string token;

    if (!(input >> token) || !isInt(token)) {
        if (input.eof() || token.empty()) {
            if (level) {
                std::cout << "WARNING : no strategy given for " << name << " in input file, using 0 1 2 as default strategy" << std::endl;
            } else {
                std::cout << "WARNING : no level nor strategy given for " << name << " in input file, using level=1 and 0 1 2 as default strategy" << std::endl;
                level = 1;
            }
            strategy = {0, 1, 2};
            return true;
        } else {
            std::cout << "ERROR : wrong strategy input for " << name << " (" << token << "), exiting ..." << std::endl;
            return false;
        }
    } else {
        try {
            strategy[0] = std::stoi(token);
            if (strategy[0] < 0 || strategy[0] > 2) {
                std::cout << "ERROR : wrong strategy input for " << name << " (" << token << "), exiting ..." << std::endl;
                return false;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR : invalid input for strategy (invalid integer: " << token << "), exiting ..." << std::endl;
            return false;
        }
    }

    if (!(input >> token) || !isInt(token)) {
        std::cout << "ERROR : incomplete strategy for " << name << " (" << strategy[0] << "), exiting ..." << std::endl;
        return false;
    } else {
        try {
            strategy[1] = std::stoi(token);
            if (strategy[1] < 0 || strategy[1] > 2) {
                std::cout << "ERROR : wrong strategy input for " << name << " (" << token << "), exiting ..." << std::endl;
                return false;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR : invalid input for strategy (invalid integer: " << token << "), exiting ..." << std::endl;
            return false;
        }
    }

    if (!(input >> token) || !isInt(token)) {
        std::cout << "ERROR : incomplete strategy for " << name << " (" << strategy[0] << " " << strategy[1] << "), exiting ..." << std::endl;
        return false;
    } else {
        try {
            strategy[2] = std::stoi(token);
            if (strategy[2] < 0 || strategy[2] > 2) {
                std::cout << "ERROR : wrong strategy input for " << name << " (" << token << "), exiting ..." << std::endl;
                return false;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR : invalid input for strategy (invalid integer: " << token << "), exiting ..." << std::endl;
            return false;
        }
    }

    if (!input.eof()) {
        std::cout << "WARNING : ignoring additional strategy inputs for " + name + " (";
        std::string additionalInput;
        bool first = true;
        while (input >> additionalInput) {
            if (!first) {
                std::cout << " ";
            }
            std::cout << additionalInput;
            first = false;
        }
        std::cout << ")" << std::endl;
    }

    return true;
}



std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
    os << p.name << " (hp: " << p.hp.toString() << ", atk: "
       << p.atk.toString() << ", def: " << p.def.toString() << ", lvl: "
       << std::to_string(p.level) << ")";
    return os;
}

Ronflex::Ronflex(int level) : Pokemon("Ronflex", level) {}
void Ronflex::setup() {
    hp.setBase(60);
    atk.setBase(45);
    def.setBase(30);

    moves.resize(3);
    moves[0] = new Headbutt();
    moves[1] = new Sleep();
    moves[2] = new Snore();
}

Dracofeu::Dracofeu(int level) : Pokemon("Dracofeu", level) {}
void Dracofeu::setup() {
    hp.setBase(50);
    atk.setBase(55);
    def.setBase(35);

    moves.resize(3);
    moves[0] = new Ember();
    moves[1] = new Reinforce();
    moves[2] = new Roar();
}

Florizarre::Florizarre(int level) : Pokemon("Florizarre", level) {}
void Florizarre::setup() {
    hp.setBase(45);
    atk.setBase(45);
    def.setBase(35);

    moves.resize(3);
    moves[0] = new Drain();
    moves[1] = new SleepPowder();
    moves[2] = new Growl();
}

Tortank::Tortank(int level) : Pokemon("Tortank", level) {}
void Tortank::setup()
{
    hp.setBase(45);
    atk.setBase(40);
    def.setBase(35);

    moves.resize(3);
    moves[0] = new WaterCanon();
    moves[1] = new Carapace();
    moves[2] = new Protect();
}

int Pokemon::number = 0;

Pokemon::~Pokemon()
{
    Pokemon::number--;
}

void Pokemon::infos()
{
    std::cout << "Number of Pokemons in the area : " + std::to_string(Pokemon::number) + "\n";
}

// Pokemon::Pokemon(const Pokemon &other)
// {
//     (void)other;
//     std::cout << "Cloning Pokemon is forbidden in this world !!!" << std::endl;
// }
