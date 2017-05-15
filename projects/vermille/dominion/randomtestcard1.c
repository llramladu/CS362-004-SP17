//Random Test for Smithy
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
        printf ("SMITHY ASSERT NOT TRUE: %s\n", error);
        //exit(0);
    }
    return 0;
}

int main() {

    int i, j, randomTests, handPosition, choice1, choice2, choice3, randomBonus, players, currentPlayer, seed, testSeed, drawDeckSize, handSize, discardPileSize;
    int *bonus;
    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    struct gameState state;

    //Start of large for loop for all the random tests
    for (randomTests = 0; randomTests < MAX_TESTS; randomTests++) {
        players = (rand() % 3) + 2;
        assertTrue(players <= 4 && players >= 2, "The number of Players is not between 1 and 4.");
        seed = (rand() % 123456780) + 1;
        testSeed = (rand() % 123456780) + 1;
        assertTrue(seed >= 1 && seed <= 123456789, "The seed is not a valid number.");
        //Initialize the gameState with random bytes
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&state)[i] = (rand() % 255);
        }
        //initializeGame(players, kingdom, seed, &state);

        //set the current player to the maximum number of players this game, player 0 is the first player
        state.numPlayers = players;
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
                    state.deck[i][j] = (rand() % 27); //0-26 possible cards
            }
            for (j = 0; j < handSize; j++) {

                state.hand[i][j] = (rand() % 27);
            }  
            for (j = 0; j < discardPileSize; j++) {

                state.discard[i][j] = (rand() % 27);
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
        int k, playCard, preHandCount = 0, postHandCount = 0, newCard;
        int testCurrentPlayer = currentPlayer;

        preHandCount = testState.handCount[testCurrentPlayer];
        playCard = cardEffect(smithy, choice1, choice2, choice2, &testState, handPosition, 0);
        postHandCount = testState.handCount[testCurrentPlayer]; 

        assertTrue(state.handCount[currentPlayer] == testState.handCount[testCurrentPlayer] + 2, "KNOWN BUG, Should draw 3 cards but will draw 4."); //This should always break, since the code is bad
        assertTrue(testState.deckCount[testCurrentPlayer] - 3 == state.deckCount[currentPlayer], "KNOWN BUG, Since 4 cards may be drawn the deck count is not correct.");
        assertTrue(testState.playedCardCount == 1, "One card, Smithy, should have been played but the count is off."); 

        //Check the other player's decks, to make sure nothings has changed
        for (k = 0; k < players; k++) {
            if (k != currentPlayer) {
                assertTrue(testState.numBuys == state.numBuys, "The number of Buys has changed and it shouldn't have.");
                assertTrue(testState.discardCount[k] == state.discardCount[k], "There are the wrong number of cards in the discard pile.");
                assertTrue(testState.handCount[k] == state.handCount[k], "The hand count is not correct.");
                assertTrue(testState.deckCount[k] == state.deckCount[k], "The draw pile has the wrong number of cards.");
            }
        }

        //cards were not gained from known supply piles.
        assertTrue(state.supplyCount[copper] == testState.supplyCount[copper], "Somehow at least one copper is missing.");
        assertTrue(state.supplyCount[silver] == testState.supplyCount[silver], "Somehow at least one silver is missing.");
        assertTrue(state.supplyCount[gold] == testState.supplyCount[gold], "Somehow at least one gold is missing.");
        assertTrue(state.supplyCount[estate] == testState.supplyCount[estate], "Somehow at least one estate is missing.");
        assertTrue(state.supplyCount[duchy] == testState.supplyCount[duchy], "Somehow at least one duchy is missing.");
        assertTrue(state.supplyCount[province] == testState.supplyCount[province], "Somehow at least one province is missing.");
        assertTrue(state.supplyCount[curse] == testState.supplyCount[curse], "Somehow at least one curse is missing.");
    }
    printf("Smithy finished all the tests!\n");
    return 0;
}