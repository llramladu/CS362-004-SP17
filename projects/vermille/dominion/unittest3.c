//Unit test for fullDeckCount function
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
        printf ("FULL DECK COUNT ASSERT NOT TRUE: %s\n", error);
        exit(0);
    }
    return 0;
}

int main (int argc, char** argv) {
    struct gameState state;

    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    int i, j, k, players, currentPlayer, seed, cardCount, functionCount;

    for (i = 0; i < MAX_TESTS; i++) {
        players = rand() % 4;
        seed = (rand() % 123456780) + 1;

        initializeGame(players, kingdom, seed, &state);

        currentPlayer = 0;

		//treasure map is last card in enum, so it should be the highest value
		cardCount = treasure_map;

		for (j = 0; j < cardCount; j++) {
	  		int count = 0;
	  		int card = j;
	  		//count number of times card appears in current player's deck
	  		for (k = 0; k < state.deckCount[currentPlayer]; k++) {
		  		if (state.deck[currentPlayer][k] == card) {
			  		count++;
		  		}
	  		}
		  	//count number of times card appears in current player's hand
		  	for (k = 0; k < state.handCount[currentPlayer]; k++) {
			  	if (state.hand[currentPlayer][k] == card) {
				  	count++;
			  	}
		  	}
	  		//count number of times card appears in current player's discount pile
	  		for (k = 0; k < state.discardCount[currentPlayer]; k++) {
		  		if (state.discard[currentPlayer][k] == card) {
			  		count++;
		  		}
	  		}
		functionCount = fullDeckCount(currentPlayer, card, &state);	  		
	  	assertTrue(functionCount == count, "The quantity of cards isn't matching.");
		}
	}

	printf("Unit Test on fullDeckCount passed!\n");
	return 0;
}