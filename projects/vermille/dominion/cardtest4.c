//Card Test for Village
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
		printf ("VILLAGE ASSERT NOT TRUE: %s\n", error);
		exit(0);
	}
	return 0;
}

int main() {

	int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

	int i, players, currentPlayer, numActions, handSize, drawDeckSize, seed;

	for (i = 0; i < MAX_TESTS; i++) {
		struct gameState state;
		players = rand() % 4;
		seed = (rand() % 123456780) + 1; //get a random seed within range

		//initialize the game state
		initializeGame(players, kingdom, seed, &state);

		currentPlayer = players;
		//Set the initiail state values
		drawDeckSize = state.deckCount[currentPlayer] = (rand() % (MAX_DECK - 12)) + 4;
		handSize = state.handCount[currentPlayer] = (rand() % (drawDeckSize - 1)) + 1;
		state.discardCount[currentPlayer] = (rand() % (drawDeckSize));
		numActions = state.numActions;

		//change turn to current currentPlayer
		state.whoseTurn = currentPlayer;

		//play the village card
		cardEffect(village, 1, 1, 1, &state, 0, 0);

		assertTrue(state.deckCount[currentPlayer] == drawDeckSize - 1, "Exactly 1 card was not drawn.");
		assertTrue(state.numActions == numActions + 2, "The number of Actions was not increased by exactly 2.");
		assertTrue(state.handCount[currentPlayer] == handSize, "The player has the wrong number of cards.");

	}

	printf("Village passed the tests!\n");
	return 0;
}