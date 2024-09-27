# Pokemonesque-Battlesimulator
This project simulates attacks between Pokemon characters. It includes a basic framework for creating and executing attacks with special effects, such as healing the attacker or causing additional damage.

## Files Included:
- **attack.cpp**: Contains the implementation of the Attack class and its derived classes (Ember, Drain, Headbutt, Sleep). Each class represents a different type of attack that a Pokemon can perform, with Drain and Headbutt having special effects.

- **attack.hpp**: The header file for attack.cpp, declaring the Attack class and its derived classes.

- **pokemon.hpp**: This header file should declare the Pokemon class, which includes attributes such as hp (health points), atk (attack points), def (defense points), level, and stunned status. It should also provide methods to modify these attributes.

## How to Compile and Run:
Ensure you have a C++ compiler installed (e.g., g++, clang++). Navigate to the project directory in your terminal and run the following commands:

```bash
# Compile the program
g++ -o pokemon_attack attack.cpp -std=c++11

# Run the program
./pokemon_attack
```
For the Python Version it should suffice to just compile the main file using Python3 and then execute it.
```bash
# Compile the program
python3 main.py
```

# Extending the Project:
- **Adding New Attacks**: To add a new attack, create a new class derived from Attack and override the specialEffect method if the attack has any special effects beyond causing damage.

- **Improving the Pokemon Class**: Enhance the Pokemon class by adding more attributes or methods, such as abilities or status effects.

- **Balancing**: Adjust the power of attacks and the health of Pokemon to make the battles more balanced and interesting

# Note:
This project is a simplified simulation and does not cover all aspects of Pokemon battles as seen in official games or media. It's intended for educational and programming practice purposes.
