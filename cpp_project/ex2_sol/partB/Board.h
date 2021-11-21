//
// Created by USER on 09/11/2021.
//

#ifndef EX2_MTM_BOARD_H
#define EX2_MTM_BOARD_H

#include <memory>
#include <iostream>
#include <vector>
#include <exception>


template<class T>
class Board {
    int row;
    int col;
    std::vector<T> board;
public:
    explicit Board(int r, int c, T val = 0) : row(r), col(c), board(r * c, val) {
        if (r < 0 || c < 0) {
            throw std::out_of_range("out of range");
        }
    }

    Board(const Board<T> &other) : row(other.row), col(other.col), board(other.row * other.col) {
        for (int i = 0; i < row * col; i++) {
            board[i] = other.board[i];
        }
    }

    Board &operator=(const Board &other) = default;

    T &operator()(int r, int c) {
        if (r < 0 || r >= row || c < 0 || c >= col) {
            throw std::out_of_range("out of range");
        }
        return board[r * col + c];
    }

    const T &operator()(int r, int c) const {
        if (r < 0 || r >= row || c < 0 || c >= col) {
            throw std::out_of_range("out of range");
        }
        return board[r * col + c];
    }

};

#endif //EX2_MTM_BOARD_H
