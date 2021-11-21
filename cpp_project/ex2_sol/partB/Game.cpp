//
// Created by USER on 09/11/2021.
//

#include "Game.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include <string>


using std::shared_ptr;
using std::make_shared;
using std::string;
using std::ostream;

void Game::boundCheck(const GridPoint &point, int row, int col) {
    if (point.row < 0 || point.col < 0 || point.row >= row || point.col >= col) {
        throw IllegalCell();
    }
}

bool Game::isEmpty(const shared_ptr<Character> &character) {
    return character == nullptr;
}

Game::Game(int height, int width) : board((height <= 0 || width <= 0) ? throw IllegalArgument()
                                                                      : height, width), row(height), col(width) {}

Game::Game(const Game &other) : board(other.row, other.col), row(other.row), col(other.col) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            if (isEmpty(other.board(i,j)) == false/* != nullptr*/) {
                board(i, j) = shared_ptr<Character>(other.board(i, j)->clone());
            }
        }
    }

}

Game &Game::operator=(const Game &other) {

    if (this == &other) {
        return *this;
    }

    board = other.board; // just for deallocate and make room if necessary
    row = other.row;
    col = other.col;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            if (isEmpty(board(i, j)) == false/* != nullptr*/) {
                board(i, j) = shared_ptr<Character>(other.board(i, j)->clone());
            }
        }
    }
    return *this;
}

void Game::addCharacter(const GridPoint &coordinates, shared_ptr<Character> character) {

    boundCheck(coordinates, row, col);

    if (board(coordinates.row, coordinates.col) != nullptr) {
        throw CellOccupied();
    }

    board(coordinates.row, coordinates.col) = character;

}

shared_ptr<Character>
Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {

    if (health <= 0 || ammo < 0 || range < 0 || power < 0) {
        throw IllegalArgument();
    }

    if (type == SOLDIER) {
        return shared_ptr<Character>(new Soldier(team, health, ammo, range, power));
    }
    if (type == SNIPER) {
        return shared_ptr<Character>(new Sniper(team, health, ammo, range, power));
    }
    if (type == MEDIC) {
        return shared_ptr<Character>(new Medic(team, health, ammo, range, power));
    }
    throw IllegalArgument();
}

void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {

    boundCheck(src_coordinates, row, col);
    boundCheck(dst_coordinates, row, col);

    if (board(src_coordinates.row, src_coordinates.col) == nullptr) {
        throw CellEmpty();
    }

    board(src_coordinates.row, src_coordinates.col)->moveCheck(src_coordinates, dst_coordinates);

    if (board(dst_coordinates.row, dst_coordinates.col) != nullptr) {
        throw CellOccupied();

    }
    board(dst_coordinates.row, dst_coordinates.col) = board(src_coordinates.row, src_coordinates.col);
    board(src_coordinates.row, src_coordinates.col) = nullptr;
}

void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    boundCheck(src_coordinates, row, col);
    boundCheck(dst_coordinates, row, col);

    if (board(src_coordinates.row, src_coordinates.col) == nullptr) {
        throw CellEmpty();

    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            GridPoint to_attack(i, j);
            board(src_coordinates.row, src_coordinates.col)->attack(board(i, j),
                                                                    dst_coordinates, to_attack, src_coordinates);
        }
    }
}

void Game::reload(const GridPoint &coordinates) {
    boundCheck(coordinates, row, col);
    if (board(coordinates.row, coordinates.col) == nullptr) {
        throw CellEmpty();
    }

    board(coordinates.row, coordinates.col)->reload();
}

ostream &mtm::operator<<(ostream &os, const Game &game) {
    string array;
    for (int i = 0; i < game.row; ++i) {
        for (int j = 0; j < game.col; ++j) {
            if (game.isEmpty(game.board(i,j))/*game.board(i, j) == nullptr*/) {
                array += ' ';
            } else {
                array += game.board(i, j)->getChar();
            }
        }
    }
    return printGameBoard(os, &array[0], &array[array.size()], game.col);

}

bool Game::isOver(Team *winningTeam) const {

    int crosser = 0, lifter = 0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; j++) {
            if (isEmpty(board(i,j)) == false/*board(i, j) != nullptr*/) {
                board(i, j)->getTeam() == CROSSFITTERS ? ++crosser : ++lifter;
            }
        }
    }

    if (crosser == 0 && lifter > 0) {
        winningTeam == nullptr ?: *winningTeam = POWERLIFTERS;
        return true;
    }

    if (lifter == 0 && crosser > 0) {
        winningTeam == nullptr ?: *winningTeam = CROSSFITTERS;
        return true;
    }

    return false;
}








