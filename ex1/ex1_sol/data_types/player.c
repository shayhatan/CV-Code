//
// Created by USER on 12/10/2021.
//

#include "player.h"
#include <stdlib.h>
#include <stdio.h>


#define NEG -1
#define WIN_POINTS 2
#define DRAW_POINTS 1
#define POS 1
#define LOSE_POINTS 0


typedef struct Player_t {
    int id;
    int wins;
    int draws;
    int loses;
    int play_time;
    bool deleted;
} Player_t;


Player playerCreate(int id) {
    Player player = malloc(sizeof(*player));
    if (player == NULL) {
        return NULL;
    }
    player->id = id;
    player->wins = 0;
    player->draws = 0;
    player->loses = 0;
    player->play_time = 0;
    player->deleted = false;
    return player;
}

Player playerCopy(Player player) {
    if (player == NULL) {
        return NULL;
    }
    Player copy_player = playerCreate(player->id);
    if (copy_player == NULL) {
        return NULL;
    }
    copy_player->wins = player->wins;
    copy_player->loses = player->loses;
    copy_player->draws = player->draws;
    copy_player->play_time = player->play_time;
    copy_player->deleted = player->deleted;
    return copy_player;
}

void playerDestroy(Player player) {
    if (player == NULL) {
        return;
    }
    free(player);
}

void playerClearStats(Player player) {
    if (player == NULL) {
        return;
    }
    player->wins = 0;
    player->draws = 0;
    player->loses = 0;
    player->play_time = 0;
    player->deleted = true;
}

void playerSetResult(Player player, PlayerResult result, int play_time) {
    if (player == NULL) {
        return;
    }
    if (result == PLAYER_WIN) {
        ++(player->wins);
    }
    if (result == PLAYER_DRAW) {
        ++(player->draws);
    }
    if (result == PLAYER_LOSE) {
        ++(player->loses);
    }
    player->play_time += play_time;
    player->deleted = false;
}

int playerGetGames(Player player) {
    if (player == NULL) {
        return NEG;
    }
    return player->loses + player->draws + player->wins;
}

int playerGetPoints(Player player) {
    if (!player) {
        return NEG;
    }
    return (WIN_POINTS * (player->wins) + DRAW_POINTS * (player->draws) + LOSE_POINTS * (player->loses));
}

float playerGetScore(Player player) {
    if (player == NULL) {
        return NEG;
    }
    return (float) playerGetPoints(player) / (float) playerGetGames(player);
}

int playerGetId(Player player) {
    if (player == NULL) {
        return NEG;
    }
    return player->id;
}

double playerGetLevel(Player player) {
    int total_games = player->wins + player->loses + player->draws;
    return (float) ((6 * (player->wins)) - (10 * (player->loses)) + (2 * (player->draws))) / ((float) total_games);
}

Player cmpPlayerScore(Player a, Player b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (playerGetScore(a) < playerGetScore(b)) {
        return b;
    }
    if (playerGetScore(a) > playerGetScore(b)) {
        return a;
    }
    //score is equal => least loses:
    if (a->loses < b->loses) {
        return a;
    }
    if (a->loses > b->loses) {
        return b;
    }
    // loses are equal => most wins
    if (a->wins < b->loses) {
        return b;
    }
    if (a->wins > b->loses) {
        return a;
    }
    //wins are equal => smaller id
    if (a->id < b->id) {
        return a;
    }
    return b;
}

bool playerExist(Player player) {
    return !(player->deleted);
}

void playerSum(Player player1, Player player2) {
    if (player1 == NULL || player2 == NULL) {
        return;
    }
    player1->wins += player2->wins;
    player1->draws += player2->draws;
    player1->loses += player2->loses;
    player1->play_time += player2->play_time;
}

void *playerCopyWrapper(void *player) {
    return (void *) playerCopy((Player) player);
}

void playerDestroyWrapper(void *player) {
    playerDestroy((Player) player);
}

void printPlayerStats(Player player) {
    printf("\n id %d \n wins %d\n draws %d\n loses %d\n", player->id, player->wins, player->draws, player->loses);
}

void playerChangeResult(Player player, PlayerResult result) {
    if (player == NULL || player->deleted == true) {
        return;
    }
    if (result == PLAYER_LOSE) {
        --(player->loses);
    }
    if (result == PLAYER_DRAW) {
        --(player->draws);
    }
    ++(player->wins);
}

double playerGetTime(Player player) {
    if (player == NULL) {
        return NEG;
    }
    return (double) player->play_time;
}

double playerGetAvg(Player player) {
    return (double) (playerGetGames(player)) / (double) (player->play_time);
}
/*
    Map to_merge: <key:player> , <data:level>
    Map players: <key:id> , <data:player>
 */




