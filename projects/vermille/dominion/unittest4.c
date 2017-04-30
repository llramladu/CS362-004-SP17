//Unit test for gainCard function
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
        printf ("GAIN CARD ASSERT NOT TRUE: %s\n", error);
        exit(0);
    }
    return 0;
}

int main (int argc, char** argv) {
    struct gameState state;

    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    int i, j, k, players, currentPlayer, seed, cardCount;

    for (i = 0; i < MAX_TESTS; i++) {
        players = rand() % 4;
        seed = (rand() % 123456780) + 1;

        initializeGame(players, kingdom, seed, &state);

		currentPlayer = 0;
  		//treasure map is last card in enum, so it should be the highest value
		cardCount = treasure_map;

  		//for each card
  		for (j = 0; j < cardCount; j++) {
	  		//for each toFlag (adding to discard, deck, and hand)
	  		for (k = 0; k < 3; k++) {
				int supplyPileQty = supplyCount(j, &state);
				int count;
				int returnValue;
				if (k == 1) {
			  		count = state.deckCount[currentPlayer];
			  		returnValue = gainCard(j, &state, k, currentPlayer);
			  		if (!returnValue) {
				  		assertTrue(state.deckCount[currentPlayer] == count + 1, "An incorrect number of cards were added to the player's deck.");
			  		}
		  		}
		  		else if (k == 2) {
			  		count = state.handCount[currentPlayer];
			  		returnValue = gainCard(j, &state, k, currentPlayer);
			  		if (!returnValue) {
				  		assertTrue(state.handCount[currentPlayer] == count + 1, "An incorrect number of cards were added to the player's hand.");
			  		}

		  		}
		  		else {
			  		count = state.discardCount[currentPlayer];
			  		returnValue = gainCard(j, &state, k, currentPlayer);
			  		if (!returnValue) {
				  		assertTrue(state.discardCount[currentPlayer] == count + 1, "An incorrect number of cards were added to the player's discard pile.");
			  		}
		  		}
		  		//check to make sure supply piles with cards are decreased by 1
		  		if (state.supplyCount[j] >= 1) {
					assertTrue(state.supplyCount[j] == supplyPileQty - 1, "Expected supply count doesn't match calculated count.");
				}
	  		}
		}

		//check to make sure function tests for supply level being empty
		state.supplyCount[0] = 0;
		assertTrue(gainCard(0, &state, 0, currentPlayer) < 0, "Attempt to take from an empty supply pile didn't cause error.");
	}
	printf("Unit Test on gainCard passed!\n");
	return 0;
}