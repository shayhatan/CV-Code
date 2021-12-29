//
// Created by USER on 09/11/2021.
//
#include "Board.h"
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"

#ifndef EX2_MTM_GAME_H
#define EX2_MTM_GAME_H

namespace mtm {
    class Game {
        Board<std::shared_ptr<Character>> board;
        int row;
        int col;

        static void boundCheck(const GridPoint &point, int row, int col);

        static bool isEmpty(const std::shared_ptr<Character> &character);

    public:
        Game(int height, int width);

        ~Game() = default;

        Game(const Game &other);

        Game &operator=(const Game &other);

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void reload(const GridPoint &coordinates);

        friend std::ostream &operator<<(std::ostream &os, const Game &game);

        bool isOver(Team *winningTeam = NULL) const;

    };

}

#endif //EX2_MTM_GAME_H
