//
// Created by USER on 12/10/2021.
//

#include "tournament.h"
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

struct Tournament_t {
    int id;
    char *location;
    int max_games;
    int winner;
};


Tournament tournamentCreate(int id, const char *location, int max_games, int winner) {
    Tournament tournament = malloc(sizeof(*tournament));
    if (tournament == NULL || location == NULL) {
        return NULL;
    }
    int size = (int) strlen(location) + 1;
    tournament->location = malloc(sizeof(*tournament->location) * size);
    if (tournament->location == NULL) {
        free(tournament);
        return NULL;
    }

    tournament->id = id;
    tournament->winner = winner;
    strcpy(tournament->location, location);
    tournament->max_games = max_games;
    return tournament;
}

Tournament tournamentCopy(Tournament tournament) {
    if (tournament == NULL) {
        return NULL;
    }
    Tournament new_tour = tournamentCreate(tournament->id, tournament->location, tournament->max_games,
                                           tournament->winner);
    if (new_tour == NULL) {
        return NULL;
    }
    return new_tour;
}

void tournamentDestroy(Tournament tournament) {
    if (tournament == NULL) {
        return;
    }
    if (tournament->location != NULL) {
        free(tournament->location);
    }
    free(tournament);
}

void printTour(Tournament tournament) {
    printf(" id is %d  \n location is %s\n", tournament->id, tournament->location);
}

/*int tournamentEnd(Tournament tournament) {
    return tournament->winner;
}*/

int tournamentGetId(Tournament tournament) {
    return tournament->id;
}


void *tournamentCopyWrapper(void *tournament) {
    return (void *) tournamentCopy((Tournament) tournament);
}

void tournamentDestroyWrapper(void *tournament) {
    tournamentDestroy((Tournament) tournament);
}

int tournamentCompareKey(Tournament a, Tournament b) {
    return a->id - b->id;
}

int tournamentCompareKeyWrapper(void *a, void *b) {
    return (int) tournamentCompareKey((Tournament) (a), (Tournament) (b));
}

int tournamentGetMaxGames(Tournament tournament) {
    if (tournament == NULL) {
        return -1;
    }
    return tournament->max_games;
}

void tournamentSetWinner(Tournament tour, int winner) {
    if (!tour) {
        return;
    }
    tour->winner = winner;
}

int tournamentGetWinner(Tournament tour) {
    if (!tour) {
        return -1;
    }
    return tour->winner;
}

char *getLocation(Tournament tour) {
    if (!tour) {
        return NULL;
    }
    return tour->location;
}
