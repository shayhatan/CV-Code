//
// Created by USER on 17/11/2021.
//

#include "Sniper.h"
#include "Exceptions.h"

#define MAX_STEPS_SNIPER 4
#define RELOAD_AMMO_SNIPER 2
#define DIVIDE_RANGE_BY 2
#define INCREASE_POWER 3
#define MULTIPLY_BY 2

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, MAX_STEPS_SNIPER, RELOAD_AMMO_SNIPER), attacked(0) {

}

Character *Sniper::clone() const {
    return new Sniper(*this);
}

bool Sniper::rangeValid(int range, int distance) {
    return FractionToCeil(range, DIVIDE_RANGE_BY) <= distance && range >= distance;
}

void
Sniper::attackCheck(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &attacker) {

    if (rangeValid(_range, GridPoint::distance(attacker, original)) == false) {
        throw OutOfRange();
    }
    if (_ammo <= 0) {
        throw OutOfAmmo();
    }

    if (target == nullptr || isSameTeam(*target)) {
        throw IllegalTarget();
    }
    // attack is valid
    --_ammo;
    ++attacked;
}

void Sniper::attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) {
    if (original == to_attack) {

        attackCheck(target, original, attacker);

        attacked % INCREASE_POWER ? target->setDamage(_power) : target->setDamage(_power * MULTIPLY_BY);

        if (target->isDead()) {
            target = nullptr;
        }
    }
}

char Sniper::getChar() const {
    if (_team == POWERLIFTERS) {
        return 'N';
    }
    return 'n';
}