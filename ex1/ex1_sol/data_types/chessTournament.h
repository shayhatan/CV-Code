//
// Created by USER on 19/10/2021.
//

#ifndef QUEENGAMBIT_SPRING21_CHESSTOURNAMENT_H
#define QUEENGAMBIT_SPRING21_CHESSTOURNAMENT_H
#include "game.h"
#include "player.h"
#include "tournament.h"
#include <stdio.h>

typedef struct GameNode_t *GameNode;

typedef struct TourNode_t *TourNode;

typedef struct Level_t *Lvl;

typedef enum{
    TOURNAMENT_OUT_OF_MEMORY,
    TOURNAMENT_PLAYER_NOT_EXIST,
    TOURNAMENT_SUCCESS,
    TOURNAMENT_NO_GAMES,
    TOURNAMENT_GAME_ALREADY_EXISTS,
    TOURNAMENT_EXCEEDED_GAMES,
    TOURNAMENT_INVALID_PLAY_TIME,
    TOURNAMENT_ERROR,
    TOURNAMENT_DOESNT_END

}TournamentResult;

/** Function to be used for copying an int as a key a the map */
void *copyKeyInt(void *n);

/** Function to be used by a map for comparing elements */
int compareInts(void *n1, void *n2);

GameNode gameNodeCreate(Game game);

/** Function used to Deallocate memory of gameNode by Allocation*/
void tourNodeDestroy(TourNode tour_node);

void gameNodeDestroy(GameNode game_node);

        void *gameNodeCopyWrapper(void *game_node);

/** Function to be used by the map for freeing a GameNode element */
void gameNodeDestroyWrapper(void *game_node);

/** Creates a tourNode type by Allocation*/
TourNode tourNodeCreate();

/** Creates a copy of tourNode type by Allocation*/
TourNode tourNodeCopy(TourNode tour_node);

/** Creates a copy of tourNode type by Allocation*//*
TourNode tourNodeCopy(TourNode tour_node);*/

/** Function to be used for copying an tourNode as a data a the map */
void *tourNodeCopyWrapper(void *tour_node);

/** Function to be used for copying an tourNode as a data a the map */
void tourNodeDestroyWrapper(void *tour_node);

/** checks if location is valid:
 *
 * @param location - a location of tournament
 * @return
 * True only if first letter is Capital and the rest must be regular letter or space
 */
bool locationValid(const char *location);

/** tournamentGameValid:
 *
 * @param chess - Target chess system
 * @param tour_data - Target Tournament, Contains games and players.
 * @param first_player - Id of one player in the game.
 * @param second_player - The id of one player in the game.
 * @return
 *             True - If the player didnt play at all or they played but the game deleted
 *             otherWise false
 */
TournamentResult tournamentGameValid(TourNode tour_data, int first_player, int second_player);

/** tournamentInsertGame: inserting a game to target tournament
 *
 * @param data - Data (games and players) of target tournament the players playing.
 * @param first_player - Target id of one player to insert to the game.
 * @param second_player - Target id of one player to insert to the game.
 * @param play_time - The time that took the players playing the game.
 * @param winner - The id of the winner, if its a draw then the id would be zero.
 * @param first - The result of the game for the first player.
 * @param second - The result of the game for the second player.
 * @param max_games -  max games allowed to each player in the Target Tournament
 * @return
 *         CHESS_OUT_OF_MEMORY - If allocation failed
 *         CHESS_EXCEEDED_GAMES - If one of the players played more games then allowed in target tournament
 */
TournamentResult tournamentInsertGame(TourNode data, int first_player, int second_player, int play_time,
                                      int winner, PlayerResult first, PlayerResult second, int max_games);

/** tournamentAddGameNode: Function add a gameNode to a target tournament
 *
 * @param chess - the whole chess system
 * @param tour - target tournament
 * @param tour_data - contains both players and games
 * @param first_player - A player
 * @param second_player - A player
 * @param winner - The winner
 * @param play_time - the time took the players the play the game.
 * @return
 *         CHESS_INVALID_TIME: If the play time is negative
  *        CHESS_OUT_OF_MEMORY - If allocation failed
 *         CHESS_EXCEEDED_GAMES - If one of the players played more games then allowed in target tournament
 *         Otherwise CHESS_SUCCESS
 */
TournamentResult tournamentAddGame(Tournament tour, TourNode tour_data, int first_player,
                                   int second_player, PlayerResult  winner, int play_time);

/** tournamentChangePlayer: Function clear the stats of target player by id from given Tournament (data in tour_data)
 *                    On the other hand update the score of the opponent to a win (if he didnt won)
 *                    The game still be recorded but as a deleted game.
 *
 * @param tour_data - Contains both the players and games
 * @param id - Target id to delete
 * @return
 *          TOURNAMENT_OUT_OF_MEMORY: If allocation failed
 *          TOURNAMENT_NULL_ARGUMENT: If NULL argument appears (should be as assert)
 *          TOURNAMENT_PLAYER_NOT_EXIST: If player isn't recorded in the given tournament
 *          otherwise TOURNAMENT_SUCCESS
 */
void tournamentChangeStats(GameNode game_node, int id, PlayerResult score);

/** tournamentRemovePlayer: Function clear the stats of target player by id from given Tournament (data in tour_data)
 *                    On the other hand update the score of the opponent to a win (if he didnt won)
 *                    The game still be recorded but as a deleted game.
 *
 * @param tour_data - Contains both the players and games
 * @param id - Target id to delete
 * @return
 *          CHESS_OUT_OF_MEMORY: If allocation failed
 *          CHESS_NULL_ARGUMENT: If NULL argument appears (should be as assert)
 *          CHESS_PLAYER_NOT_EXIST: If player isn't recorded in the given tournament
 *          otherwise CHESS_SUCCESS
 */
TournamentResult tournamentRemovePlayer(TourNode tour_data, int id);

/** tournamentInsertWinner:
 *
 * @param tour : Target tournament to insert the winner
 * @param players : Map of players to search who is the player with the best stats
 * @return
 *              TOURNAMENT_OUT_OF_MEMORY: If allocation failed
 *              TOURNAMENT_NO_GAMES: If there is no active player
 *              otherwise: TOURNAMENT_SUCCESS
 */
TournamentResult tournamentInsertWinner(Tournament tour, Map players);

/** Function returns the map of games of a target tournament*/
Map tournamentGetGames(TourNode tour);

/** Function returns the player of a target tournament*/
Map tournamentGetPlayers(TourNode tour);

/** Function returns single game from a target game_node*/
Game gameGet(GameNode game_node);

/** Function returns first player from a target game_node*/
Player playerGetFirst(GameNode game_node);

/** Function returns second player from a target game_node*/
Player playerGetSecond(GameNode game_node);

void *copyKeyLevel(void *level);


int cmpLevel(Player a, Player b);

int cmpLevelWrapper(void *a, void *b);

int levelGetId(Lvl level);

double levelGet(Lvl level);

Lvl levelCopy(Lvl level);

void *levelCopyWrapper(void *level);

TournamentResult mapLevels(Map levels, Map players);

TournamentResult levelPrint(FILE* file,Map levels);

TournamentResult tournamentSaveStatics(FILE * file,TourNode tour_node, char *path_file
                                       ,const char *location, int winner);

void setWinner(TourNode tour_data, int winner);

bool tournamentEnd(TourNode tour_data);

int getWinner(TourNode tour_data);


#endif //QUEENGAMBIT_SPRING21_CHESSTOURNAMENT_H
