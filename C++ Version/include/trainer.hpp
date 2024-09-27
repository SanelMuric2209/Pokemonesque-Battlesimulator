#pragma once
#include <iostream>
#include "macro.h"
#include "pokemon.hpp"
#include <fstream>

class TeamRocket {
public:
    TeamRocket();
    static Pokemon* pokemons[MAX_POKEBALL];
    static void infos();
};

class Trainer {
public:
    Trainer();
    bool encounter(std::ifstream& world); // read 1 line in world.txt
    Pokemon* pokemons[MAX_POKEBALL];
};
