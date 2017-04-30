//Card Test for Adventurer
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
		printf ("ADVENTURER ASSERT NOT TRUE: %s\n", error);
		exit(0);
	}
	return 0;
}

int main() {
	//Setting up the Kingdom
	int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

	int i, j, players, currentPlayer, drawDeckSize, handSize, discardPileSize, treasuresInHand, currentTresures, numActions, seed, zCards, adventurerDiscarded = 1;

	for (i = 0; i < MAX_TESTS; i++) {
		
		//values need to be reset each test
		treasuresInHand = 0; 
		currentTresures = 0;

		struct gameState state;
		players = rand() % 4;
		seed = (rand() % 123456780) + 1; //get a random seed within range

		//initialize the game state
		initializeGame(players, kingdom, seed, &state);

		currentPlayer = 0;

		//Set the initial state values: at least 4 cards to draw from, 
		//5 cards in hand and what those cards are, a check to make sure 
		//there are not too many cards in the discard pile, and the current number of actions.
		drawDeckSize = state.deckCount[currentPlayer] = (rand() % (MAX_DECK - 12)) + 4;
		for (j = 0; j < drawDeckSize; j++) {

			state.deck[currentPlayer][j] = rand() % (treasure_map);
		}
		handSize = 5;
		state.handCount[currentPlayer] = handSize;
		state.hand[currentPlayer][0] = adventurer;
		state.hand[currentPlayer][1] = estate;
		state.hand[currentPlayer][2] = estate;
		state.hand[currentPlayer][3] = estate;
		state.hand[currentPlayer][4] = estate;
		discardPileSize = (rand() % (drawDeckSize));
		while ((discardPileSize + drawDeckSize + 2) > MAX_DECK) {
			discardPileSize = (rand() % (drawDeckSize - 2));
		}
		state.discardCount[currentPlayer] = discardPileSize;
		for (j = 0; j < discardPileSize; j++) {

			state.discard[currentPlayer][j] = rand() % (treasure_map);
		}
		numActions = state.numActions;


		//play the card with the current player
		state.whoseTurn = currentPlayer;

		//Get the current number of treasures which should be 0
		for (j = 0; j < state.handCount[currentPlayer]; j++) {

			if (state.hand[0][j] == copper || state.hand[0][j]  == silver || state.hand[0][j]  == gold) {

				treasuresInHand += 1;
				//printf("treasuresInHand %d\n", treasuresInHand);
			}
		}		

		//play Adventurer
		cardEffect(adventurer, 1, 1, 1, &state, 0, 0);

		for (j = 0; j < state.handCount[currentPlayer]; j++) {

			if (state.hand[0][j] == copper || state.hand[0][j]  == silver || state.hand[0][j]  == gold) {

				currentTresures += 1;
				//printf("currentTresures %d\n", currentTresures);
			}
			else if (state.hand[0][j] == adventurer) {

				adventurerDiscarded = 0;
			}

		}

		assertTrue(treasuresInHand + 2 >= currentTresures, "More than 2 treasures were added to the player's hand.");
		assertTrue(adventurerDiscarded = 1, "The Adventurer card is still in the player's hand.");

	}

	printf("Adventurer passed the tests!\n");
	return 0;
}
