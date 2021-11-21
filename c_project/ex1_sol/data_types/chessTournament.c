//
// Created by USER on 19/10/2021.
//

#include "chessTournament.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


#define SPACE ' '
#define EMPTY NULL
#define POS 1
#define NEG -1


/*
        The struct will be the part of "Chess" struct
        Made to ease implantation and improve running time complexity

        Game - single game
        Player - will be a pointer to actual player ( heap smart management )
 */
struct GameNode_t {
    Game game;
    Player player1;
    Player player2;
};

/*
        The struct will be the part of "Chess" struct
        Made to ease implantation and improve running time complexity

        Map players: A map of players while
        Key  - id_player
        Data -  Player ( Allocated )

        Map games_nodes: A map of players while
        Key  - The number of games played
        Data - The data is GameNode ( A Game data type and Pointers to two players )
 */
struct TourNode_t {
    Map players;
    Map games_nodes;
    int winner;
};

struct Level_t {
    int id;
    double level;
};

static Lvl levelCreate() {
    Lvl level = malloc(sizeof(*level));
    if (level == NULL) {
        return NULL;
    }
    return level;
}

/*------------------------------------------- Static functions-------------------------------------*/
static TournamentResult gameLongestTime(Map node_games, int *longest_time, int *total_time) {
    GameNode game_node = NULL;
    int game_time;
    MAP_FOREACH(int*, it, node_games) {
        if (it == NULL) {
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        game_node = mapGet(node_games, it);
        if (game_node == NULL) {
            free(it);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        game_time = gameGetTime(game_node->game);
        if (*longest_time < game_time) {
            *longest_time = game_time;
        }
        *total_time += game_time;
        free(it);
    }
    return TOURNAMENT_SUCCESS;
}

int levelGetId(Lvl level) {
    return level->id;
}

double levelGet(Lvl level) {
    return level->level;
}

Lvl levelCopy(Lvl level) {
    Lvl copy = malloc(sizeof(*copy));
    if (copy == NULL) {
        return NULL;
    }
    copy->id = level->id;
    copy->level = level->level;
    return copy;
}

void *levelCopyWrapper(void *level) {
    return (void *) (levelCopy((Lvl) level));
}

int cmpLevel(Player a, Player b) {
    if (playerGetLevel(a) == playerGetLevel(b) || playerGetId(a) == playerGetId(b)) {
        return playerGetId(a) - playerGetId(b);
    }
    if (playerGetScore(a) > playerGetScore(b)) {
        return NEG;
    }
    return POS;
}

int cmpLevelWrapper(void *a, void *b) {
    return (int) cmpLevel((Player) a, (Player) b);
}

void *copyKeyInt(void *n) {
    if (!n) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

int compareInts(void *n1, void *n2) {
    return (*(int *) n1 - *(int *) n2);
}

GameNode gameNodeCreate(Game game) {
    GameNode new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return NULL;
    }
    new_node->game = gameCopy(game);
    new_node->player1 = NULL;
    new_node->player2 = NULL;
    return new_node;
}

static GameNode gameNodeCopy(GameNode game_node) {
    if (game_node == NULL) {
        return NULL;
    }
    GameNode new_node = gameNodeCreate(game_node->game);
    if (new_node == NULL) {
        return NULL;
    }
    new_node->player1 = game_node->player1;
    new_node->player2 = game_node->player2;
    return new_node;
}

void *gameNodeCopyWrapper(void *game_node) {
    return (void *) gameNodeCopy((GameNode) game_node);
}

void gameNodeDestroy(GameNode game_node) {
    if (game_node == NULL) {
        return;
    }
    if (game_node->game == NULL) {
        free(game_node);
        return;
    }
    gameDestroy(game_node->game);
    free(game_node);
}

void gameNodeDestroyWrapper(void *game_node) {
    gameNodeDestroy((GameNode) game_node);
}

TourNode tourNodeCreate() {
    TourNode tour_node = malloc(sizeof(*tour_node));
    if (tour_node == NULL) {
        return NULL;
    }
    tour_node->players = mapCreate(playerCopyWrapper, copyKeyInt, playerDestroyWrapper, free, compareInts);
    if (tour_node->players == NULL) {
        free(tour_node);
        return NULL;
    }
    tour_node->games_nodes = mapCreate(gameNodeCopyWrapper, copyKeyInt, gameNodeDestroyWrapper, free, compareInts);
    if (tour_node->games_nodes == NULL) {
        mapDestroy(tour_node->players);
        free(tour_node);
        return NULL;
    }
    tour_node->winner = 0;
    return tour_node;
}

TourNode tourNodeCopy(TourNode tour_node) {
    TourNode new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return NULL;
    }
    new_node->players = mapCopy(tour_node->players);
    if (new_node->players == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->games_nodes = mapCopy(tour_node->games_nodes);
    if (new_node->games_nodes == NULL) {
        mapDestroy(new_node->players);
        free(new_node);
        return NULL;
    }
    new_node->winner = tour_node->winner;
    return new_node;
}

void *tourNodeCopyWrapper(void *tour_node) {
    return (void *) tourNodeCopy((TourNode) tour_node);
}

void tourNodeDestroy(TourNode tour_node) {
    if (tour_node == NULL) {
        return;
    }
    mapDestroy(tour_node->players);
    mapDestroy(tour_node->games_nodes);
    free(tour_node);
}

void tourNodeDestroyWrapper(void *tour_node) {
    tourNodeDestroy((TourNode) tour_node);
}

void *copyKeyLevel(void *level) {
    if (!level) {
        return NULL;
    }
    double *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(double *) level;
    return copy;
}

bool locationValid(const char *location) {
    if (!(location[0] <= 'Z' && location[0] >= 'A')) {
        return false;
    }
    int len = (int) strlen(location);
    for (int i = 1; i < len; i++) {
        if (!(location[i] == SPACE || (location[i] >= 'a' && location[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}

TournamentResult tournamentGameValid(TourNode tour_data, int first_player, int second_player) {
    bool valid_game = true;
    MAP_FOREACH(int*, it, tour_data->games_nodes) {
        if (it == NULL) {
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        GameNode game_node = mapGet(tour_data->games_nodes, it);
        if (gameValid(game_node->game, first_player, second_player) == false) {
            valid_game = false;
        }
        free(it);
    }
    if (valid_game == false) {
        return TOURNAMENT_GAME_ALREADY_EXISTS;
    }
    return TOURNAMENT_SUCCESS;
}

TournamentResult tournamentInsertGame(TourNode data, int first_player, int second_player, int play_time,
                                      int winner, PlayerResult first, PlayerResult second, int max_games) {
    MapResult result;

    Player player1 = mapGet(data->players, &first_player);
    bool player1_exist = true;
    if (player1 == NULL) {
        player1_exist = false;
        player1 = playerCreate(first_player);
        if (player1 == NULL) {
            return TOURNAMENT_OUT_OF_MEMORY;
        }
    }
    Player player2 = mapGet(data->players, &second_player);
    bool player2_exist = true;
    if (player2 == NULL) {
        player2_exist = false;
        player2 = playerCreate(second_player);
        if (player2 == NULL) {
            playerDestroy(player1);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
    }

    if (playerGetGames(player1) >= max_games || playerGetGames(player2) >= max_games) {
        return TOURNAMENT_EXCEEDED_GAMES;
    }

    playerSetResult(player1, first, play_time);
    playerSetResult(player2, second, play_time);

    if (player1_exist == false) {
        result = mapPut(data->players, &first_player, player1);
        playerDestroy(player1);
        if (result != MAP_SUCCESS) {
            playerDestroy(player2);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
    }

    if (player2_exist == false) {
        result = mapPut(data->players, &second_player, player2);
        playerDestroy(player2);
        if (result != MAP_SUCCESS) {
            playerDestroy(player1);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
    }

    Game game = gameCreate(first_player, second_player, play_time, winner);
    if (game == NULL) {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    GameNode game_node = gameNodeCreate(game);
    if (game_node == NULL) {
        return TOURNAMENT_OUT_OF_MEMORY;
    }

/*       notice that if its not the first game of the player (player isn't new)
         we wouldn't have to use mapGet (O(n) running time)                                          */
    game_node->player1 = mapGet(data->players, &first_player);
    game_node->player2 = mapGet(data->players, &second_player);

    int size = mapGetSize(data->games_nodes);
    result = mapPut(data->games_nodes, &size, game_node);
    gameNodeDestroy(game_node);
    if (result != MAP_SUCCESS) {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    return TOURNAMENT_SUCCESS;

}

TournamentResult tournamentAddGame(Tournament tour, TourNode tour_data, int first_player,
                                   int second_player, PlayerResult winner, int play_time) {

    TournamentResult res = tournamentGameValid(tour_data, first_player, second_player);
    if (res != TOURNAMENT_SUCCESS) {
        return res;
    }
    if (play_time < 0) {
        return TOURNAMENT_INVALID_PLAY_TIME;
    }
    int max_games = tournamentGetMaxGames(tour);

    if (winner == PLAYER_FIRST) {
        res =
                tournamentInsertGame(tour_data, first_player, second_player, play_time, first_player, PLAYER_WIN,
                                     PLAYER_LOSE, max_games);
    }
    if (winner == PLAYER_SECOND) {
        res =
                tournamentInsertGame(tour_data, first_player, second_player, play_time, second_player, PLAYER_LOSE,
                                     PLAYER_WIN, max_games);

    }
    if (winner == PLAYER_DRAW) {
        res =
                tournamentInsertGame(tour_data, first_player, second_player, play_time, 0,
                                     PLAYER_DRAW, PLAYER_DRAW, max_games);
    }

    tournamentDestroy(tour);
    return res;

}

void tournamentChangeStats(GameNode game_node, int id, PlayerResult score) {
    GameResult game_result = gameGetOpponent(game_node->game, id);
    if (score == PLAYER_WIN) {
        game_result = gameGetOpponent(game_node->game, id);
        if (game_result == ID_OPPONENT_FIRST) {
            playerClearStats(game_node->player2);
        }
        if (game_result == ID_OPPONENT_SECOND) {
            playerClearStats(game_node->player1);
        }
    }
    if (game_result == ID_OPPONENT_FIRST) {
        playerChangeResult(game_node->player1, score);
        playerClearStats(game_node->player2);
    }
    if (game_result == ID_OPPONENT_SECOND) {
        playerChangeResult(game_node->player2, score);
        playerClearStats(game_node->player1);
    }
}


TournamentResult tournamentRemovePlayer(TourNode tour_data, int id) {
    GameNode game_node = EMPTY;
    GameResult game_result;
    bool game_exist = false;
    MAP_FOREACH(int*, it, tour_data->games_nodes) {
        if (it == NULL) {
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        game_node = mapGet(tour_data->games_nodes, it);
        game_result = gameDeletePlayer(game_node->game, id);

        if (game_result == GAME_REMOVE) {
            playerClearStats(game_node->player1);
            playerClearStats(game_node->player2);
            free(it);
            mapRemove(tour_data->games_nodes, it);
            return TOURNAMENT_SUCCESS;
        }

        assert(game_result != GAME_NULL_ARGUMENT);
        assert(game_node->player1 && game_node->player2);

        if (game_result == OPPONENT_DRAW) {
            game_exist = true;
            tournamentChangeStats(game_node, id, PLAYER_DRAW);

        }

        if (game_result == OPPONENT_LOSE) {
            game_exist = true;
            tournamentChangeStats(game_node, id, PLAYER_DRAW);

        }

        if (game_result == OPPONENT_WON) {
            game_exist = true;
            tournamentChangeStats(game_node, id, PLAYER_WIN);
        }

        free(it);
    }
    if (game_exist != true) {
        return TOURNAMENT_PLAYER_NOT_EXIST;
    }
    return TOURNAMENT_SUCCESS;
}

TournamentResult tournamentInsertWinner(Tournament tour, Map players) {
    Player winner = EMPTY;
    Player player = EMPTY;
    int counter = 0;
    MAP_FOREACH(int*, it, players) {
        if (it == NULL) {
            free(it);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        player = mapGet(players, it);
        if (counter == 0) {
            winner = player;
        } else {
            winner = cmpPlayerScore(winner, player);
        }
        ++counter;
        free(it);
    }
    if (winner != NULL && playerExist(player)) {
        tournamentSetWinner(tour, playerGetId(winner));
        return TOURNAMENT_SUCCESS;
    }
    return TOURNAMENT_NO_GAMES;
}

Map tournamentGetPlayers(TourNode tour) {
    if (tour == NULL) {
        return NULL;
    }
    return tour->players;
}

Map tournamentGetGames(TourNode tour) {
    if (tour == NULL) {
        return NULL;
    }
    return tour->players;
}

Game gameGet(GameNode game_node) {
    if (game_node == NULL) {
        return NULL;
    }
    return game_node->game;
}

Player playerGetFirst(GameNode game_node) {
    if (game_node == NULL) {
        return NULL;
    }
    return game_node->player1;
}

Player playerGetSecond(GameNode game_node) {
    if (game_node == NULL) {
        return NULL;
    }
    return game_node->player2;
}

TournamentResult mapLevels(Map levels, Map players) {
    Player player = NULL;
    Lvl level = levelCreate();
    if (level == NULL) {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    MAP_FOREACH(int *, it, players) {
        if (it == NULL) {
            free(level);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        player = mapGet(players, it);
        level->id = *it;
        level->level = playerGetLevel(player);
        if (mapPut(levels, player, level) != MAP_SUCCESS) {
            free(level);
            free(it);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        free(it);
    }
    free(level);
    return TOURNAMENT_SUCCESS;
}

TournamentResult levelPrint(FILE *file, Map levels) {

    MAP_FOREACH(Player, it, levels) {
        if (it == NULL) {
            free(it);
            return TOURNAMENT_OUT_OF_MEMORY;
        }
        Lvl lvl = mapGet(levels, it);
        fprintf(file, "%d %.2lf\n", lvl->id, lvl->level);
        free(it);
    }
    return TOURNAMENT_SUCCESS;
}

void setWinner(TourNode tour_data, int winner) {
    tour_data->winner = winner;
}

TournamentResult tournamentSaveStatics(FILE *file, TourNode tour_node,
                                       char *path_file, const char *location, int winner
) {
    if (!path_file || !location || !winner) {
        return
                TOURNAMENT_ERROR;
    }
    TournamentResult result;
    int longest_time = 0;
    int total_time = 0;
    int num_of_games = mapGetSize(tour_node->games_nodes);
    int num_of_players = mapGetSize(tour_node->players);
    result = gameLongestTime(tour_node->games_nodes, &longest_time, &total_time);
    if (result != TOURNAMENT_SUCCESS) {
        return
                result;
    }
    double avg_time = (double) total_time / (double) num_of_games;
    fprintf(file,
            "%d\n%d\n%.2lf\n%s\n%d\n%d\n", winner, longest_time,
            avg_time, location, num_of_games, num_of_players);

    return
            TOURNAMENT_SUCCESS;

}

bool tournamentEnd(TourNode tour_data) {
    return (tour_data->winner != 0);
}

int getWinner(TourNode tour_data) {
    return tour_data->winner;
}








