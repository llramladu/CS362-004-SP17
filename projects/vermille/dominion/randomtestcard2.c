//Random Test for Sea Hag
//Leanne Vermillion
//05/14/17

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
        printf ("SEA HAG ASSERT NOT TRUE: %s\n", error);
        //exit(0);
    }
    return 0;
}

int main() {

    int i, j, randomTests, handPosition, choice1, choice2, choice3, randomBonus, players, currentPlayer, seed, testSeed, drawDeckSize, handSize, discardPileSize;
    int *bonus;
    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    //Start of large for loop for all the random tests
    for (randomTests = 0; randomTests < MAX_TESTS; randomTests++) {
    	struct gameState state;
        players = (rand() % 3) + 2;
        assertTrue(players <= 4 && players >= 2, "The number of Players is not between 1 and 4.");
        seed = (rand() % 123456780) + 1;
        testSeed = (rand() % 123456780) + 1;
        assertTrue(seed >= 1 && seed <= 123456789, "The seed is not a valid number.");
        //Initialize the gameState with random bytes
        //for (i = 0; i < sizeof(struct gameState); i++) {
        //    ((char*)&state)[i] = (rand() % 255);
        //}
        initializeGame(players, kingdom, seed, &state);

        //set the current player to the maximum number of players this game, player 0 is the first player
        //state.numPlayers = players;
        currentPlayer = (players - 1);
        state.whoseTurn = currentPlayer;

        //Sets the values to possible numbers, sets deck count low to increase chance of shuffleing
        for (i = 0; i < players; i++) {
            drawDeckSize = state.deckCount[i] = (rand() % 10) + 2;
            handSize = state.handCount[i] = (rand() % 12) + 2;
            discardPileSize = state.discardCount[i] = (rand() % (MAX_DECK/2)) + 2;
            state.playedCardCount = 0;
            state.numBuys = 1;
            //Set cards to valid card numbers 
            for (j = 0; j < drawDeckSize; j++) {
                    state.deck[i][j] = (rand() % 26) + 1; //1-26 possible cards but not curses
            }
            for (j = 0; j < handSize; j++) {

                state.hand[i][j] = (rand() % 26) + 1;
            }  
            for (j = 0; j < discardPileSize; j++) {

                state.discard[i][j] = (rand() % 26) + 1;
            }
        }

        //Set the card position in the current player's hand
        handPosition = (rand() % (state.handCount[currentPlayer]));

        //Set random but legal values for options when playing a card.
        choice1 = (rand() % 256);
        choice2 = (rand() % 256);
        choice3 = (rand() % 256);
        randomBonus = (rand() % 256);
        bonus = &randomBonus;

        //Make a copy of the current state to test
        struct gameState testState;
        testState = state;

        //more varibles for the test case
        int k, playCard;
        int testCurrentPlayer = currentPlayer;

        playCard = cardEffect(sea_hag, choice1, choice2, choice3, &testState, handPosition, bonus);

        //checks to make sure other player's states haven't changed.
        for (k = 0; k < players; k++) {
            if (k != currentPlayer) {
                assertTrue(testState.numBuys == state.numBuys, "The number of Buys has changed and it shouldn't have.");
                assertTrue(testState.discardCount[k] == state.discardCount[k] + 1, "There are the wrong number of cards in the discard pile.");
                assertTrue(testState.handCount[k] == state.handCount[k], "The hand count is not correct.");
                //printf("Cards in deck test %d, state %d\n", testState.deckCount[k], state.deckCount[k]);
                assertTrue(testState.deckCount[k] == state.deckCount[k] - 1, "The draw pile has the wrong number of cards.");
                assertTrue(testState.hand[k][0] == curse, "A curse was not added to the player's hand at the 0 position.");
            }
        }
		
		assertTrue((state.discardCount[currentPlayer] == testState.discardCount[testCurrentPlayer]), "KNOWN BUG, the number of cards in the current player's discard pile changed and shouldn't have. ");

        //cards were not gained from known supply piles.
        assertTrue(state.supplyCount[copper] == testState.supplyCount[copper], "Somehow at least one copper is missing.");
        assertTrue(state.supplyCount[silver] == testState.supplyCount[silver], "Somehow at least one silver is missing.");
        assertTrue(state.supplyCount[gold] == testState.supplyCount[gold], "Somehow at least one gold is missing.");
        assertTrue(state.supplyCount[estate] == testState.supplyCount[estate], "Somehow at least one estate is missing.");
        assertTrue(state.supplyCount[duchy] == testState.supplyCount[duchy], "Somehow at least one duchy is missing.");
        assertTrue(state.supplyCount[province] == testState.supplyCount[province], "Somehow at least one province is missing.");
        assertTrue(state.supplyCount[curse] == testState.supplyCount[curse] - (players - 1), "The curse pile doesn't have the right number of cards.");

	}
	printf("Sea Hag finished all the tests!\n");
	return 0;
}