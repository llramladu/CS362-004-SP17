//Unit test for isGameOver function
//Leanne Vermillion
//04/29/17

//Needed Headers
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
//Libraries Used
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//Global Variable
#define MAX_TESTS 1000

int assertTrue(int test, char* error) {
    if (!test) {
        printf ("GAME OVER ASSERT NOT TRUE: %s\n", error);
        exit(0);
    }
    return 0;
}

int main (int argc, char** argv) {

    struct gameState state;

    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    int i, players, drawDeckSize, seed;

    for (i = 0; i < MAX_TESTS; i++) {
        players = (rand() % 4) + 1;
        seed = (rand() % 123456780) + 1; //get a random seed within range

        //printf ("Starting game.\n");  
        initializeGame(players, kingdom, seed, &state);

        //even seeds remove 3 supply piles, odd remove all the Provence cards.
        if (seed % 2 == 0) {
            //set 3 supply piles to empty, this should end the game.
            state.supplyCount[0] = 0;
            state.supplyCount[1] = 0;
            state.supplyCount[2] = 0;
            assertTrue(isGameOver(&state) == 1, "There are 3 supply piles empty, but the game isn't over.");
        }
        //if there are no more Province cards, game over
        else {
            state.supplyCount[province] = 0;
            assertTrue(isGameOver(&state) == 1, "There are no Province cards, but the game isn't over." );
        }
    }
    printf("Unit Test on isGameOver passed!\n");
    return 0;
}