//
// Created by USER on 14/10/2021.
//
#include <stdio.h>
#include <stdlib.h>


#include "chessSystem.h"
#include "data_types/chessTournament.h"

#define SPACE ' '
#define EMPTY NULL;
#define DIDNT_END 0
#define NEG -1


struct chess_system_t {
    Map tournaments;
};

/*------------------------- static functions ------------------------------*/
static ChessResult convertEnum(TournamentResult result) {
    if (result == TOURNAMENT_OUT_OF_MEMORY) {
        return CHESS_OUT_OF_MEMORY;
    }
    if (result == TOURNAMENT_PLAYER_NOT_EXIST) {
        return CHESS_PLAYER_NOT_EXIST;
    }
    if (result == TOURNAMENT_SUCCESS) {
        return CHESS_SUCCESS;
    }
    if (result == TOURNAMENT_NO_GAMES) {
        return CHESS_NO_GAMES;
    }
    if (result == TOURNAMENT_INVALID_PLAY_TIME) {
        return CHESS_INVALID_PLAY_TIME;
    }
    if (result == TOURNAMENT_DOESNT_END) {
        return CHESS_NO_TOURNAMENTS_ENDED;
    }
    return CHESS_SAVE_FAILURE;
}

static PlayerResult getPlayerWinner(Winner winner) {
    if (winner == DRAW) {
        return PLAYER_DRAW;
    }
    if (winner == FIRST_PLAYER) {
        return PLAYER_FIRST;
    }
    if (winner == SECOND_PLAYER) {
        return PLAYER_SECOND;
    }
    return PLAYER_SUCCESS;
}

static ChessResult mergePlayers(Map to_merge, Map players) {
    Player player = NULL;
    Player inserted_player = NULL;
    MAP_FOREACH(int *, it, players) {
        if (it == NULL) {
            return CHESS_OUT_OF_MEMORY;
        }
        inserted_player = mapGet(to_merge, it);
        player = mapGet(players, it);
        if (inserted_player == NULL) {
            if (mapPut(to_merge, it, player) != MAP_SUCCESS) {
                free(it);
                return CHESS_OUT_OF_MEMORY;
            }
        } else {
            playerSum(inserted_player, player);
        }
        free(it);
    }
    return CHESS_SUCCESS;
}


/*-------------------------------- Head file functions --------------------------------------------------*/

ChessSystem chessCreate() {
    ChessSystem chess = malloc(sizeof(*chess));
    if (chess == NULL) {
        return NULL;
    }
    chess->tournaments = mapCreate(tourNodeCopyWrapper, tournamentCopyWrapper, tourNodeDestroyWrapper,
                                   tournamentDestroyWrapper, tournamentCompareKeyWrapper);
    if (chess->tournaments == NULL) {
        free(chess);
        return NULL;
    }
    return chess;
}

void chessDestroy(ChessSystem chess) {
    if (chess == NULL) {
        return;
    }
    mapDestroy(chess->tournaments);
    free(chess);
}

ChessResult chessAddTournament(ChessSystem chess, int tournament_id,
                               int max_games_per_player, const char *tournament_location) {
    if (chess == NULL || tournament_location == NULL) {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0) {
        return CHESS_INVALID_ID;
    }
    if (mapContains(chess->tournaments, &tournament_id)) {
        return CHESS_TOURNAMENT_ALREADY_EXISTS;
    }
    if (locationValid(tournament_location) == false) {
        return CHESS_INVALID_LOCATION;
    }
    if (max_games_per_player <= 0) {
        return CHESS_INVALID_MAX_GAMES;
    }
    Tournament tournament = tournamentCreate(tournament_id, tournament_location, max_games_per_player, 0);
    if (tournament == NULL) {
        free(chess);
        return CHESS_OUT_OF_MEMORY;
    }
    TourNode tour_node = tourNodeCreate();
    if (tour_node == NULL) {
        tournamentDestroy(tournament);
        free(chess);
        return CHESS_OUT_OF_MEMORY;
    }
    MapResult result = mapPut(chess->tournaments, tournament, tour_node);
    if (result != MAP_SUCCESS) {
        tourNodeDestroy(tour_node);
        tournamentDestroy(tournament);
        chessDestroy(chess);
        return CHESS_OUT_OF_MEMORY;
    }

    return CHESS_SUCCESS;
}

ChessResult chessRemoveTournament(ChessSystem chess, int tournament_id) {
    if (chess == NULL) {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0) {
        return CHESS_INVALID_ID;
    }
    MapResult result = mapRemove(chess->tournaments, &tournament_id);
    if (result == MAP_ITEM_DOES_NOT_EXIST) {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time) {
    if (chess == NULL) {
        return CHESS_NULL_ARGUMENT;
    }
    if (first_player <= 0 || second_player <= 0 || tournament_id <= 0 || first_player == second_player) {
        return CHESS_INVALID_ID;
    }
    Tournament tour = EMPTY;
    TourNode tour_data = EMPTY;
    MAP_FOREACH(Tournament, it, chess->tournaments) {
        if (it == NULL) {
            return CHESS_OUT_OF_MEMORY;
        }
        if (tournamentGetId(it) == tournament_id) {
            tour = it;
            tour_data = mapGet(chess->tournaments, it);
            if (tour_data == NULL) {
                return CHESS_NULL_ARGUMENT;
            }
            if (!tournamentEnd(tour_data)) {
                TournamentResult result =
                        tournamentAddGame(tour, tour_data, first_player, second_player,
                                          getPlayerWinner(winner), play_time);
                return convertEnum(result);
            }
            tournamentDestroy(it);
            return CHESS_TOURNAMENT_ENDED;

        }
        tournamentDestroy(it);
    }
    return CHESS_TOURNAMENT_NOT_EXIST;
}

ChessResult chessRemovePlayer(ChessSystem chess, int player_id) {
    if (chess == NULL) {
        return CHESS_NULL_ARGUMENT;
    }
    if (player_id <= 0) {
        return CHESS_INVALID_ID;
    }
    TourNode tour_data = EMPTY;
    bool player_exist = false;
    TournamentResult tour_result;
    ChessResult result;
    MAP_FOREACH(Tournament, it, chess->tournaments) {
        if (it == NULL) {
            chessDestroy(chess);
            return CHESS_OUT_OF_MEMORY;
        }
        tour_data = mapGet(chess->tournaments, tour_data);
        if (!tournamentEnd(tour_data)) {
            tour_result = tournamentRemovePlayer(tour_data, player_id);
            result = convertEnum(tour_result);
            if (result == CHESS_OUT_OF_MEMORY) {
                chessDestroy(chess);
                return CHESS_OUT_OF_MEMORY;
            }
            if (result != CHESS_PLAYER_NOT_EXIST) {
                player_exist = true;
            }
        }
        tournamentDestroy(it);
    }
    if (player_exist == false) {
        return CHESS_PLAYER_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

ChessResult chessEndTournament(ChessSystem chess, int tournament_id) {
    if (tournament_id <= 0) {
        return CHESS_INVALID_ID;
    }
    Tournament tour = EMPTY;
    TourNode tour_data = EMPTY;
    TournamentResult tour_result;
    ChessResult result;
    MAP_FOREACH(Tournament, it, chess->tournaments) {
        if (it == NULL) {
            return CHESS_OUT_OF_MEMORY;
        }
        if (tournamentGetId(it) == tournament_id) {
            tour = it;
            tour_data = mapGet(chess->tournaments, it);
            if (tour_data == NULL) {
                return CHESS_NULL_ARGUMENT;
            }
            if (!tournamentEnd(tour_data)) {
                tour_result = tournamentInsertWinner(tour, tournamentGetPlayers(tour_data));
                result = convertEnum(tour_result);
                setWinner(tour_data, tournamentGetWinner(it));
                tournamentDestroy(it);
                if (result == CHESS_OUT_OF_MEMORY) {
                    chessDestroy(chess);
                }
                return result;
            }
            tournamentDestroy(it);
            return CHESS_TOURNAMENT_ENDED;

        }
        tournamentDestroy(it);
    }
    return CHESS_TOURNAMENT_NOT_EXIST;
}

double chessCalculateAveragePlayTime(ChessSystem chess, int player_id, ChessResult *chess_result) {
    if (chess == NULL) {
        *chess_result = CHESS_NULL_ARGUMENT;
        return NEG;
    }
    if (player_id <= 0) {
        *chess_result = CHESS_INVALID_ID;
        return NEG;
    }
    Map to_merge =
            mapCreate(playerCopyWrapper, copyKeyInt, playerDestroyWrapper, free, compareInts);
    if (to_merge != MAP_SUCCESS) {
        *chess_result = CHESS_OUT_OF_MEMORY;
        chessDestroy(chess);
        return NEG;
    }
    TourNode tour_data = NULL;
    MAP_FOREACH(Tournament, it, chess->tournaments) {

        if (it == NULL) {
            mapDestroy(to_merge);
            *chess_result = CHESS_OUT_OF_MEMORY;
            chessDestroy(chess);
            return NEG;
        }
        tour_data = mapGet(chess->tournaments, it);
        *chess_result = mergePlayers(to_merge, tournamentGetPlayers(tour_data));
        if (*chess_result != CHESS_SUCCESS) {
            mapDestroy(to_merge);
            free(it);
            chessDestroy(chess);
            return NEG;
        }
        free(it);
    }
    Player player = mapGet(to_merge, &player_id);
    if (player == NULL) {
        *chess_result = CHESS_PLAYER_NOT_EXIST;
        return NEG;
    }
    *chess_result = CHESS_SUCCESS;
    return playerGetAvg(player);
}

ChessResult chessSavePlayersLevels(ChessSystem chess, FILE *file) {
    Map levels =
            mapCreate(levelCopyWrapper, playerCopyWrapper, free, playerDestroyWrapper, cmpLevelWrapper);
    TournamentResult result;
    if (chess == NULL) {
        return CHESS_NULL_ARGUMENT;
    }
    if (!file) {
        return CHESS_SAVE_FAILURE;
    }
    if (levels == NULL) {
        chessDestroy(chess);
        return CHESS_OUT_OF_MEMORY;
    }
    MAP_FOREACH(Tournament, it, chess->tournaments) {
        TourNode tour_data = NULL;
        if (it == NULL) {
            mapDestroy(levels);
            chessDestroy(chess);
            return CHESS_OUT_OF_MEMORY;
        }
        tour_data = mapGet(chess->tournaments, it);
        result = mapLevels(levels, tournamentGetPlayers(tour_data));
        if (result != TOURNAMENT_SUCCESS) {
            mapDestroy(levels);
            free(it);
            chessDestroy(chess);
            return CHESS_OUT_OF_MEMORY;
        }
        free(it);
    }
    result = levelPrint(file, levels);
    mapDestroy(levels);
    return convertEnum(result);
}

ChessResult chessSaveTournamentStatistics(ChessSystem chess, char *path_file) {
    TournamentResult result = TOURNAMENT_DOESNT_END;
    if (chess == NULL || path_file == NULL) {
        return CHESS_NULL_ARGUMENT;
    }

    FILE *file = fopen(path_file, "w");
    if (file == NULL) {
        return CHESS_SAVE_FAILURE;
    }
    TourNode tour_data = NULL;
    MAP_FOREACH(Tournament, it, chess->tournaments) {
        if (it == NULL) {
            chessDestroy(chess);
            return CHESS_OUT_OF_MEMORY;
        }
        tour_data = mapGet(chess->tournaments, it);
        if (tournamentEnd(tour_data)) {
            char* location = getLocation(it);
            result =
            tournamentSaveStatics(file, tour_data, path_file, location,
                                  getWinner(tour_data));
            if(result == TOURNAMENT_OUT_OF_MEMORY){
                free(it);
                chessDestroy(chess);
            }

        }
        free(it);
    }
    fclose(file);
    return convertEnum(result);
}






