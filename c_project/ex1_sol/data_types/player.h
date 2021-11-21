//
// Created by USER on 12/10/2021.
//

#ifndef QUEENGAMBIT_SPRING21_PLAYER_H
#define QUEENGAMBIT_SPRING21_PLAYER_H
#include <stdbool.h>
#include "../mtm_map/map.h"
/** Player Data Type
 *
 *  the following function are available:
 *
 *  createPlayer: Allocates a new player - has no recorded games
 *
 *  playerCopy: Creates a copy of target player
 *
 *  playerCopy: Creates a copy of target player
 *
 *  playerDestroy: Deallocates an existing player
 *
 *  playerClearStats: set all data to be empty and indicates the player was deleted
 *
 *  playerSetResult: Adding data (WIN/DRAW/LOSE, play_time) to target Player
 *
 *  playerGetPoints: returns total points of a target player
 *
 *  playerGetScore: returns player_score of a target player
 *  player_score = ( num_of_wins * 2 + num_of_draws * 1 ) / ( num_of_games_of_player )
 *
 *  cmpPlayerScore:  calculate the rate of the 2 targets and returns the target id with the highest rate.
 *
 *  */

typedef struct Player_t* Player;

/*
    Type for specifying who is the winner in a certain match
*/
typedef enum {
    PLAYER_WIN,
    PLAYER_LOSE,
    PLAYER_DRAW,
    PLAYER_OUT_OF_MEMORY,
    PLAYER_SUCCESS,
    PLAYER_FIRST,
    PLAYER_SECOND
}PlayerResult;

/** playerCreate: Allocates a new player - has no recorded games
 *
 * @param id - Player id, assuming id is VALID!
 * @return
 * NULL - if memory allocation failed
 * Otherwise - The new player
 */
Player playerCreate(int id);

/** playerCopy: Creates a copy of target player
 *
 * @param player - Target player
 * @return
 * NULL - if a NULL was sent or a memory allocation failed.
 * Otherwise - A copy of Target player
 */
Player playerCopy(Player player);

/** playerDestroy: Deallocates an existing player
 *
 * @param player - Target player to be deallocated.
 * If Player is NULL nothing will be done
 */
void playerDestroy(Player player);

/** playerClearStats: set all data to empty and indicates the player was deleted
 * means no games recorded
 *
 * @param player - Target player to be clear
 * If player is NULL nothing will be done
 */
void playerClearStats(Player player);

/** playerSetResult: Adding data (WIN/DRAW/LOSE, play_time) to target Player
 *
 * @param player - target player to add data
 * @param result - enum of possible result WIN/DRAW/LOSE
 * @param play_time - time it took to the game, assuming play_time is VALID!
 * If player is NULL nothing will be done
 */
void playerSetResult(Player player, PlayerResult result, int play_time);

/** playerGetPoints: returns total points of a target player
 *
 * @param player - Target player
 * @return - Sum of target player wins value, lose value, draw value
 * If player is NULL the function returns negative number
 */
int playerGetPoints(Player player);

/** playerGetGames: returns number of games of a target player
 *
 * @param player - Target player
 * @return - Number of games
 * If player is NULL returns negative number
 */
int playerGetGames(Player player);

/** playerGetScore: returns player_score of a target player
 * player_score = ( num_of_wins * 2 + num_of_draws * 1 ) / ( num_of_games_of_player )
 *
 * @param player - Target player
 * @return the player_score
 * If player is NULL returns negative number
 */
float playerGetScore(Player player);

/** playerGetId:
 *
 * @param player Target player
 * @return id of the player
 * If player is NULL returns negative number
 */
int playerGetId(Player player);

/**playerGetLevel: return a level of target player
 * player = (6*num_of_wins -10*num_of_loses + 2*num_of_draws)/(num_of_games)
 *
 * assumptions: player must not be null
 * @param player: Target player
 * @return level
 */
double playerGetLevel(Player player);

/**cmpPlayerScore:  calculate the rate of the 2 targets and returns the target id with the highest rate.
 *rate: the player with the highest score:
 *player_score = ( num_of_wins * 2 + num_of_draws * 1 ) / ( num_of_games_of_player )
 *If two players have the same score, the player with least losses will be chosen.
 *If two players have the same number of losses, the player with the most wins will be chosen
 *If two players have the same number of wins and losses,
 *the player with smaller id will be chosen.
 *
 * @param a - One of two targets
 * @param b - One of two targets
 * @return
 * If one of the players is NULL returns negative number
 * otherwise returns id of the player with higher rate
 */
Player cmpPlayerScore(Player a, Player b);

void printPlayerStats(Player player);

void playerSum(Player player1, Player player2);

bool playerExist(Player player);

void playerChangeResult(Player player, PlayerResult result);

/** Function to be used for copying an Player as a data to the map*/
void *playerCopyWrapper(void *player);

void playerDestroyWrapper(void *player);

double playerGetAvg(Player player);


#endif //QUEENGAMBIT_SPRING21_PLAYER_H
