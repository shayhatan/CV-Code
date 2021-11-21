//
// Created by USER on 17/11/2021.
//

#ifndef EX2_MTM_SNIPER_H
#define EX2_MTM_SNIPER_H

#include "Character.h"

using namespace mtm;

class Sniper : public Character {
    int attacked;

    void
    attackCheck(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &attacker);

    static bool rangeValid(int range, int distance);

public:
    Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);

    Character *clone() const override;

    char getChar() const override;

    void
    attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) override;


};

#endif //EX2_MTM_SNIPER_H
