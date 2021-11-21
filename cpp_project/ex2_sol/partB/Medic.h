//
// Created by USER on 17/11/2021.
//

#ifndef EX2_MTM_MEDIC_H
#define EX2_MTM_MEDIC_H
#include "Character.h"

class Medic : public Character{
    void
    attackCheck(std::shared_ptr<Character> &target, const GridPoint &original, const GridPoint &attacker);

public:
    Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);

    Character *clone() const override;

    char getChar() const override;

    void
    attack(std::shared_ptr<Character> &target, GridPoint original, GridPoint to_attack, GridPoint attacker) override;
};




#endif //EX2_MTM_MEDIC_H
