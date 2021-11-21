//
// Created by USER on 12/10/2021.
//

#ifndef QUEENGAMBIT_SPRING21_GAME_H
#define QUEENGAMBIT_SPRING21_GAME_H
#include <stdbool.h>


typedef struct Game_t* Game;

/** gameCreate: create a game with given data, assuming all data is VALID!!!
 *
 * @param player1 - first player  id
 * @param player2  - second player id
 * @param play_time - the time the game took
 * @param winner_id - if draw winner id = 0 else one of the players id
 * @return
 *          Null if memory allocation failed
 *          otherwise Game
 */
Game gameCreate(int player1, int player2, int play_time, int winner_id);

/** gameDestroy: Deallocates an existing game
 *
 * @param game - Target game to be deallocated.
 * If Game is NULL nothing will be done
 */
void gameDestroy(Game game);

/**gameCopy: create a copy of given game
 *
 * @param game - Target game to copy
 * @return
 *          NULL - if game is null or memory allocation failed
 *          Game - copy of game
 */
Game gameCopy(Game game);

/** gameValid: the function check if the game is already recorded,
 * if it does then if the game deleted then its valid, means true;
 *
 * @param game  - the game to check if the id's recorded
 * @param id1 - id of one of the player, we assuming the id is valid
 * @param id2 - id of one of the player, we assuming the id is valid
 * @return
 * FALSE - if Game is NULL or game recorded and not deleted
 * other wise TRUE
 */
bool gameValid(Game game, int id1, int id2);

typedef enum GameResult_t{
    ID_NOT_EXIST,
    OPPONENT_WON,
    OPPONENT_DRAW,
    OPPONENT_LOSE,
    ID_OPPONENT_FIRST,
    ID_OPPONENT_SECOND,
    GAME_NULL_ARGUMENT,
    GAME_REMOVE,
    GAME_SUCCESS
}GameResult;

/** gameDeletedPlayer: delete a player by given id, change the status of the game to deleted
 * returns the enum of the score from point of view of the opponent.
 *
 *
 * @param game - the game to delete the player
 * @param id - the id to delete, we assuming that id is valid
 * @return
 *              ID_DOESNT_EXIST - If the Target id didnt play in the target game or game was deleted
 *              OPPONENT_LOSE - If the player against the target id lose
 *              OPPONENT_WON - If the player against the target id won
 *              OPPONENT_DRAW - If it was a draw in game
 *
 */
GameResult gameDeletePlayer(Game game, int id);

/** gameGetOpponent:
 *
 * @param game - Target game
 * @param id - Target id the check who is the player that played against him
 * @return
 *          ID_DOESNT_EXIST - If the Target id didnt play in the target game
 *          ID_OPPONENT_FIRST - If id equals to the id of player2
 *          ID_OPPONENT_SECOND - If id equals to the id of player1
 */
GameResult gameGetOpponent(Game game, int id);

/** Function to be used for copying an Game as a data to the map*/
void *gameCopyWrapper(void *game);

void printfGame(Game game);

int gameGetTime(Game game);
#endif //QUEENGAMBIT_SPRING21_GAME_H
