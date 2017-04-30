//Card Test for Great Hall
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
#define MAX_TESTS 10000

int assertTrue(int test, char* error) {
	if (!test) {
		printf ("GREAT HALL ASSERT NOT TRUE: %s\n", error);
		exit(0);
	}
	return 0;
}

int main() {
	//Setting up the Kingdom
	int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

	int i, players, currentPlayer, drawDeckSize, handSize, numActions, seed;

	for (i = 0; i < MAX_TESTS; i++) {
		struct gameState state;
		players = rand() % 4;
		seed = (rand() % 123456780) + 1; //get a random seed within range

		//Initialize the game state
		initializeGame(players, kingdom, seed, &state);

		currentPlayer = players;

		//Set the initial state values: at least 4 cards to draw from, 
		//at least 1 card in hand, that there might be cards in the discard pile,
		//and the current number of actions.
		drawDeckSize = state.deckCount[currentPlayer] = (rand() % (MAX_DECK - 12)) + 4;
		handSize = state.handCount[currentPlayer] = (rand() % (drawDeckSize - 1)) + 1;
		state.discardCount[currentPlayer] = (rand() % (drawDeckSize));
		numActions = state.numActions;

		//play the card with the current player
		state.whoseTurn = currentPlayer;

		//play Great Hall
		cardEffect(great_hall, 1, 1, 1, &state, handSize-1, 0);

		assertTrue(state.numActions == numActions + 1, "The number of actions was not increased by 1.");
		assertTrue(state.deckCount[currentPlayer] == drawDeckSize - 1, "The deck count was not decreased by 1." );
		assertTrue(state.handCount[currentPlayer] == handSize, "The player has the wrong number of cards.");
	  }

	printf("Great Hall passed the tests!\n");

	return 0;
}