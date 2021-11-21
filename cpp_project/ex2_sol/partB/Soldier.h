//
// Created by USER on 10/11/2021.
//

#ifndef EX2_MTM_SOLDIER_H
#define EX2_MTM_SOLDIER_H

#include "Character.h"


using namespace mtm;

class Soldier : public Character {
    bool
    attackValid(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &to_attack,
                const GridPoint& attacker);

    static bool rangeAroundValid(const GridPoint &a, const GridPoint &b, int range);

    static int damageAround(int power);

public:
    Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);

    Character *clone() const override;

    char getChar() const override;

    void
    attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) override;

};

#endif //EX2_MTM_SOLDIER_H
