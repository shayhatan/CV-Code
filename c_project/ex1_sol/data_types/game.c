//
// Created by USER on 12/10/2021.
//

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define NEG -1

struct Game_t {
    int player1;
    int player2;
    int play_time;
    int winner;
    bool deleted;
};

Game gameCreate(int player1, int player2, int play_time, int winner_id) {
    Game game = malloc(sizeof(*game));
    if (game == NULL) {
        return NULL;
    }
    game->player1 = player1;
    game->player2 = player2;
    game->play_time = play_time;
    game->winner = winner_id;
    game->deleted = false;
    return game;
}

void gameDestroy(Game game) {
    if (game == NULL) {
        return;
    }
    free(game);
}

Game gameCopy(Game game) {
    if (game == NULL) {
        return NULL;
    }
    Game new_game = malloc(sizeof(*new_game));
    if (new_game == NULL) {
        return NULL;
    }
    new_game->player1 = game->player1;
    new_game->player2 = game->player2;
    new_game->play_time = game->play_time;
    new_game->winner = game->winner;
    new_game->deleted = game->deleted;
    return new_game;
}

bool gameValid(Game game, int id1, int id2) {
    if (game == NULL) {
        return false;
    }
    if (game->player1 == id1 && game->player2 == id2) {
        return !game->deleted;
    }
    if (game->player2 == id1 && game->player1 == id1) {
        return !game->deleted;
    }
    return true;
}

GameResult gameDeletePlayer(Game game, int id) {
    if (game == NULL) {
        return GAME_NULL_ARGUMENT;
    }
    if (game->deleted == true) {
        if ((game->player1 == id && game->winner == game->player2) ||
            (game->player2 == id && game->winner == game->player1)) {
            return GAME_REMOVE;
        }
        return ID_NOT_EXIST;
    }
    if (game->player1 == id) {
        game->deleted = true;
        assert(game->deleted == false);
        if (game->winner == game->player1) {
            return OPPONENT_LOSE;
        }
        if (game->winner == game->player2) {
            return OPPONENT_WON;
        }
        return OPPONENT_DRAW;
    }
    if (game->player2 == id) {
        game->deleted = true;
        if (game->winner == game->player2) {
            return OPPONENT_LOSE;
        }
        if (game->winner == game->player1) {
            return OPPONENT_WON;
        }
        return OPPONENT_DRAW;
    }
    return ID_NOT_EXIST;

}

GameResult gameGetOpponent(Game game, int id) {
    if (game == NULL) {
        return GAME_NULL_ARGUMENT;
    }
    if (game->player1 == id) {
        return ID_OPPONENT_SECOND;
    }
    if (game->player2 == id) {
        return ID_OPPONENT_FIRST;
    }
    return ID_NOT_EXIST;
}

void printfGame(Game game) {
    printf("\n play_time %d\n , winner %d\n ", game->play_time, game->winner);
}

void *gameCopyWrapper(void *game) {
    return (void *) gameCopy((Game) game);
}

int gameGetTime(Game game) {
    return game->play_time;
}
