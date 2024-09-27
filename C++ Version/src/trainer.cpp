#include "../include/trainer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using std::cout, std::endl, std::ifstream, std::string;

Trainer::Trainer() {
    for (int i = 0; i < MAX_POKEBALL; ++i) {
        pokemons[i] = nullptr;
    }
}

Pokemon* TeamRocket::pokemons[MAX_POKEBALL] = {nullptr};

void TeamRocket::infos()
{
    std::cout << "Pokemon stolen by TeamRocket :\n";
    for (int i = 0; i < MAX_POKEBALL; i++) {
        Pokemon* p = TeamRocket::pokemons[i];
        if (p != nullptr) {
            std::cout << "- " << *p << "\n";
        }
    }
}


bool Trainer::encounter(ifstream& world) {
    Pokemon* p = nullptr;
    string name; world >> name;

    if (name == "TeamRocket") {
        if (pokemons[0] != nullptr) {
            for (int i = 0; i < MAX_POKEBALL; ++i) {
                if (TeamRocket::pokemons[i] == nullptr) {
                    TeamRocket::pokemons[i] = pokemons[0];
                    break;
                }
            }

            for (int i = 0; i < MAX_POKEBALL - 1; ++i) {
                pokemons[i] = pokemons[i + 1];
            }
            pokemons[MAX_POKEBALL - 1] = nullptr;
        }
        return true;
    }

    int level; world >> level;
    if (level < 0) {
        cout << "ERROR : negative level for "+name+", exiting ..." << endl;
        return false;
    }

    if (name == "Ronflex") {
        p = new Ronflex(level);
    } else if (name == "Dracofeu") {
        p = new Dracofeu(level);
    } else if (name == "Florizarre") {
        p = new Florizarre(level);
    } else if (name == "Tortank") {
        p = new Tortank(level);
    } else {
        cout << "ERROR : encountered unknown Pokemon ("+name+"), exiting ..." << endl;
        return false;
    }

    string line;
    std::getline(world, line);
    std::stringstream ss(line);
    if (!(p->readStrategy(ss))) return false;
    
    p->setup();

    int i = 0;
    while (i < MAX_POKEBALL) {
        if (pokemons[i] == nullptr) {
            cout << " -- captured : " << *p << endl;
            pokemons[i] = p;
            break;
        }
        i++;
    }

    if (i == MAX_POKEBALL) {
        int n = 0;
        try {
            bool enemyAlive = true;
            while (n < MAX_POKEBALL && pokemons[n] != nullptr) {
                pokemons[n]->rest();
                bool mainWins = pokemons[n]->fightWith(*p);
                if (mainWins) {
                    enemyAlive = false;
                    cout << " -- " << *pokemons[n] << " won against " << *p << endl;
                    pokemons[n]->levelUp();
                    delete p; p = nullptr;
                    break;
                } else {
                    cout << " -- " << *pokemons[n] << " lost against " << *p << endl;
                    delete pokemons[n];
                    for (int c = n; c < MAX_POKEBALL - 1; c++) {
                        pokemons[c] = pokemons[c + 1];
                        if (pokemons[c + 1] == nullptr) break; // optional
                    }
                    pokemons[MAX_POKEBALL - 1] = nullptr;
                    p->restart();
                }
            }
            if (enemyAlive) delete p;
        } catch(...) {
            // idk why it fixes the out_of_bouds error for test nr 2
        }
    }

    return true;
}
