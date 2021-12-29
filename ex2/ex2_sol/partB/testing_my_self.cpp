//
// Created by USER on 10/11/2021.
//


#include "Game.h"
#include <iostream>
#include "Exceptions.h"
#include <memory>
#include <string>

using std::string;

int main() {
    std::cout << "------Soldier TEST------" << std::endl;
    Game g1(8, 8);
    g1.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(1, 4), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g1 << std::endl;
    g1.move(GridPoint(1, 1), GridPoint(1, 2));
    std::cout << g1 << std::endl;
    g1.attack(GridPoint(1, 4), GridPoint(1, 2));
    g1.attack(GridPoint(1, 4), GridPoint(1, 2));
    std::cout << g1 << std::endl;

    if (g1.isOver()) {
        std::cout << std::endl << std::endl << "Soldier TEST [OK]" << std::endl << std::endl;
    }

    std::cout << "------Sniper TEST------" << std::endl;
    Game g2(8, 8);
    g2.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 2, 4, 5));
    g2.addCharacter(GridPoint(1, 4), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g2 << std::endl;
    g2.move(GridPoint(1, 1), GridPoint(1, 2));
    std::cout << g2 << std::endl;
    g2.attack(GridPoint(1, 4), GridPoint(1, 2));
    g2.attack(GridPoint(1, 4), GridPoint(1, 2));
    std::cout << g2 << std::endl;
    std::cout << std::endl << std::endl << "Sniper TEST [OK]" << std::endl << std::endl;

    std::cout << "------MEDIC TEST------" << std::endl;
    Game g3(8, 8);
    g3.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 2, 4, 5));
    g3.addCharacter(GridPoint(1, 4), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g3 << std::endl;
    g3.move(GridPoint(1, 1), GridPoint(1, 2));
    std::cout << g3 << std::endl;
    g3.attack(GridPoint(1, 4), GridPoint(1, 2));
    g3.attack(GridPoint(1, 4), GridPoint(1, 2));
    std::cout << g3 << std::endl;
    std::cout << std::endl << std::endl << "Sniper TEST [OK]" << std::endl << std::endl;
}