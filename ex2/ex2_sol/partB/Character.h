//
// Created by USER on 10/11/2021.
//

#ifndef EX2_MTM_CHARACTER_H
#define EX2_MTM_CHARACTER_H

#include <memory>
#include "Auxiliaries.h"


using namespace mtm;

class Character {
protected:
    Team _team;
    units_t _health;
    units_t _ammo;
    units_t _range;
    units_t _power;
    units_t _move; // max cells allowed to move
    units_t _reload; // how many units of ammo to add

   // static int damageAround(units_t power); // encase its not the actual target (only in range)

    static int FractionToCeil(int numerator, int denominator); // encase its not the actual target (only in range)

    //bool rangeAroundValid(const GridPoint &a, const GridPoint &b) const;

    bool rangeValid(const GridPoint &a, const GridPoint &b) const;

    bool isSameTeam(Character &other);

public:

    Character(Team team, units_t health, units_t ammo, units_t range, units_t power,
              units_t move, units_t reload);


    virtual ~Character() = default;

    Character(const Character &character) = default;

    virtual Character *clone() const = 0;

    virtual void
    attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) = 0;

    void moveCheck(const GridPoint& a,const GridPoint& b) const;

    void reload();

    virtual char getChar() const = 0;

    bool isDead() const;

    void setDamage(int damage);

    Team getTeam() const;

    void setHealth(units_t power);

};


#endif //EX2_MTM_CHARACTER_H
