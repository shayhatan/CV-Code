//
// Created by USER on 10/11/2021.
//
#include "Soldier.h"
#include "Exceptions.h"

#define MAX_STEPS_SOLDIER 3
#define RELOAD_AMMO_SOLDIER 3
#define DIVIDE_POWER_BY 2
#define DIVIDE_RANGE_BY 3

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, MAX_STEPS_SOLDIER, RELOAD_AMMO_SOLDIER) {

}

Character *Soldier::clone() const {
    return new Soldier(*this);
}

int Soldier::damageAround(int power) {
    return FractionToCeil(power, DIVIDE_POWER_BY);
}

bool Soldier::rangeAroundValid(const GridPoint &a, const GridPoint &b, int range) {
    return FractionToCeil(range, DIVIDE_RANGE_BY) >= GridPoint::distance(a, b);
}

bool
Soldier::attackValid(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &to_attack,
                     const GridPoint &attacker) {

    if (rangeValid(attacker, original) == false) {
        throw OutOfRange();
    }

    if (to_attack <= original) {
        if (_ammo <= 0) {
            throw OutOfAmmo();
        }
    }

    if (original.row != attacker.row && original.col != attacker.col) {
        throw IllegalTarget();
    }

    //attack the source target valid
    if(to_attack == original) {
        --_ammo;
    }


    if(target == nullptr || isSameTeam(*target)) {
        return false;
    }


    if (target == nullptr && to_attack != original) {
        return false;
    }

    return rangeAroundValid(to_attack, original, _range);
}

void Soldier::attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) {
    if (attackValid(target, original, to_attack, attacker) == false) {
        return;
    }

    original == to_attack ? target->setDamage(_power) : target->setDamage(damageAround(_power));

    if (target->isDead()) {
        target = nullptr;
    }
}

char Soldier::getChar() const {
    if (_team == POWERLIFTERS) {
        return 'S';
    }
    return 's';
}






