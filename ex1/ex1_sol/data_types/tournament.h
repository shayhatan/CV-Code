//
// Created by USER on 12/10/2021.
//

#ifndef QUEENGAMBIT_SPRING21_TOURNAMENT_H
#define QUEENGAMBIT_SPRING21_TOURNAMENT_H

#include <stdbool.h>


typedef struct Tournament_t *Tournament;

Tournament tournamentCreate(int id, const char *location, int max_games, int winner);

Tournament tournamentCopy(Tournament tournament);

void tournamentDestroy(Tournament tournament);

void printTour(Tournament tournament);

int tournamentGetId(Tournament tournament);

/** Function to be used for copying an Tournament as a data to the map*/
void *tournamentCopyWrapper(void *tournament);

/** Function to be used by the map for freeing elements */
void tournamentDestroyWrapper(void *tournament);

int tournamentCompareKey(Tournament a, Tournament b);

int tournamentCompareKeyWrapper(void *a, void *b);

int tournamentGetMaxGames(Tournament tournament);

void tournamentSetWinner(Tournament tour, int winner);

int tournamentGetWinner(Tournament tour);

char *getLocation(Tournament tour);


#endif //QUEENGAMBIT_SPRING21_TOURNAMENT_H