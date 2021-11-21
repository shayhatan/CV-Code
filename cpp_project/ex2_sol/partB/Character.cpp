//
// Created by USER on 10/11/2021.
//

#include "Character.h"
#include "cmath"
#include "Exceptions.h"

Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power,
                     units_t move, units_t reload) :
        _team(team), _health(health), _ammo(ammo), _range(range), _power(power), _move(move),
        _reload(reload) {

}

bool Character::rangeValid(const GridPoint &a, const GridPoint &b) const {
    return _range >= GridPoint::distance(a, b);
}

void Character::reload() {
    _ammo += _reload;
}

bool Character::isDead() const {
    return _health <= 0;
}

bool Character::isSameTeam(Character &other) {
    return _team == other._team;
}

void Character::setDamage(int damage) {
    _health -= damage;
}

Team Character::getTeam() const {
    return _team;
}

void Character::moveCheck(const GridPoint &a, const GridPoint &b) const {
    if (_move < GridPoint::distance(a, b)) {
        throw MoveTooFar();
    }
}

int Character::FractionToCeil(int numerator, int denominator) {
    return ceil(double(numerator) / double(denominator));
}

void Character::setHealth(units_t power) {
    _health += power;
}








