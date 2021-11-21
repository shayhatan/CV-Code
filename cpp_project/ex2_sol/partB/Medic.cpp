//
// Created by USER on 17/11/2021.
//
#include "Medic.h"
#include "Exceptions.h"

#define MAX_STEPS_MEDIC 5
#define RELOAD_AMMO_MEDIC 5

Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) :
        Character(team, health, ammo, range, power, MAX_STEPS_MEDIC, RELOAD_AMMO_MEDIC) {
}

Character *Medic::clone() const {
    return new Medic(*this);
}

void Medic::attackCheck(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &attacker) {
    if (rangeValid(attacker, original) == false) {
        throw OutOfRange();
    }
    if (_ammo <= 0) {
        throw OutOfAmmo();
    }

    if (target == nullptr || original == attacker) {
        throw IllegalTarget();
    }
}

void Medic::attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) {

    if (original == to_attack) {

        attackCheck(target, original, attacker);

        if (isSameTeam(*target)) {
            target->setHealth(_power);
        } else {
            target->setDamage(_power);
            --_ammo;
        }

        if (target->isDead()) {
            target = nullptr;
        }
    }

}

char Medic::getChar() const {
    if (_team == POWERLIFTERS) {
        return 'M';
    }
    return 'm';
}


