#include <cassert>
#include <type_traits>

#include "./include/trainer.hpp"

int main() {
    Trainer sacha;

    std::ifstream inputFile("world.txt");
    if (!inputFile.is_open()) {
        std::cout << "ERROR : no world.txt file found, exiting ..." << std::endl;
        return 1;
    }

    std::cout << "Wandering in the high grass ..." << std::endl;
    bool cont = true;
    while (!inputFile.eof() && cont) {
        cont = sacha.encounter(inputFile); 
    }
    if (cont) {
        Pokemon::infos();
        TeamRocket::infos();
    }

    return 0;
}

// int main() {
//     static_assert(std::is_abstract_v<Pokemon>);
//     static_assert(!std::is_copy_constructible_v<Dracofeu>);

//     assert(Pokemon::number == 0);
//     Dracofeu d1(1);
//     Tortank t1(2);
//     Ronflex r1(1);
//     assert(Pokemon::number == 3);
//     Pokemon* p = new Tortank(1);
//     assert(Pokemon::number == 4);
//     delete p;
//     assert(Pokemon::number == 3);
// }
