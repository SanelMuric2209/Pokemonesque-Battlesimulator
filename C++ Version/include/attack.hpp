#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include "pokemon.hpp"
using std::string, std::min, std::max, std::floor;

class Pokemon;
class Attack {
    int power;
public:
    Attack(int power = 0);
    int getDamage(const Pokemon& caster, const Pokemon& target);
    void execute(Pokemon& caster, Pokemon& target);
    virtual void specialEffect(Pokemon& caster, Pokemon& target, int dmg);
};
class Ember : public Attack {
public:
    Ember();
};

class Drain : public Attack {
public:
    Drain();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Headbutt : public Attack {
public:
    Headbutt();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Sleep : public Attack {
public:
    Sleep();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Snore : public Attack {
public:
    Snore();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Reinforce : public Attack {
public:
    Reinforce();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Roar : public Attack {
public:
    Roar();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class SleepPowder : public Attack {
public:
    SleepPowder();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Growl : public Attack {
public:
    Growl();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class WaterCanon : public Attack {
public:
    WaterCanon();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Carapace : public Attack {
public:
    Carapace();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};

class Protect : public Attack {
public:
    Protect();
    void specialEffect(Pokemon& caster, Pokemon& target, int dmg) override;
};
