#include "attack.hpp"
#include "pokemon.hpp"
#include <string>
#include <cmath>

Attack::Attack(int power) : power(power) {}

int Attack::getDamage(const Pokemon& caster, const Pokemon& target) {
    if (power == 0) return 0;

    double P = static_cast<double>(power);
    double A = static_cast<double>(caster.atk.current);
    double LA = static_cast<double>(caster.level);
    double D = static_cast<double>(target.def.current);
    double LD = static_cast<double>(target.level);
    double LM = (LA + LD) / 2.0;

    double damage = std::max(P * (A * LA - D * LD) / (100.0 * LM), 0.0) + 1;
    return static_cast<int>(std::floor(damage));
}

void Attack::execute(Pokemon& caster, Pokemon& target) {
    int dmg = getDamage(caster, target);
    if (!caster.stunned) {
        target.hp.modify(-dmg);
        specialEffect(caster, target, dmg);
    } else {
        caster.stunned = false;
        specialEffect(caster, target, 0);
    }
}

void Attack::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)caster; (void)target; (void)dmg;  // This silences unused parameter warnings.
}

Ember::Ember() : Attack(20) {}

Drain::Drain() : Attack(15) {}
void Drain::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)target;
    int healAmount = static_cast<int>(0.5 * dmg + 1);
    caster.hp.modify(healAmount);
}

Headbutt::Headbutt() : Attack(25) {}
void Headbutt::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)target;
    caster.hp.modify(-4);
}

Sleep::Sleep() : Attack(0) {}
void Sleep::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)target;
    caster.hp.modify(14);
    caster.asleep = true;
}

Snore::Snore() : Attack(0) {}
void Snore::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)caster;
    target.def.modify(-1);
}

Reinforce::Reinforce() : Attack(0) {}
void Reinforce::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)target;
    caster.def.modify(1);
}

Roar::Roar() : Attack(0) {}
void Roar::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)target;
    caster.atk.modify(1);
}

SleepPowder::SleepPowder() : Attack(0) {}
void SleepPowder::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)caster;
    target.asleep = true;
}

Growl::Growl() : Attack(0) {}
void Growl::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)caster;
    target.atk.modify(-1);
}

WaterCanon::WaterCanon() : Attack(15) {}
void WaterCanon::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)caster;
    target.def.modify(-1);
}

Carapace::Carapace() : Attack(0) {}
void Carapace::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)target;
    caster.def.modify(2);
}

Protect::Protect() : Attack(0) {}
void Protect::specialEffect(Pokemon& caster, Pokemon& target, int dmg) {
    (void)dmg;
    (void)caster;
    target.stunned = true;
}
