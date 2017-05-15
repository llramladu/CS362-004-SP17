//Random Test for Adventurer
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
#define MAX_TESTS 150

int assertTrue(int test, char* error) {
    if (!test) {
        printf ("ADVENTURER ASSERT NOT TRUE: %s\n", error);
        //exit(0);
    }
    return 0;
}

int main() {

    int i, j, randomTests, handPosition, choice1, choice2, choice3, randomBonus, players, currentPlayer, seed, testSeed, drawDeckSize, handSize, discardPileSize;
    int *bonus;
    //int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};

    struct gameState state;

    //Start of large for loop for all the random tests
    for (randomTests = 0; randomTests < MAX_TESTS; randomTests++) {
        //printf("RandomTest: %d\n", randomTests);
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
            state.playedCardCount = (rand() % 5);
            state.numBuys = 1;
            //Set cards to valid card numbers (with more treasure cards mixed in)
            for (j = 0; j < drawDeckSize; j++) {
                if (i%6 == 0) {
                    state.deck[i][j] = (rand() % 3) + 4; //treasures are numbers 4, 5, & 6
                } 
                else {
                    state.deck[i][j] = (rand() % 27); //0-26 possible cards
                }
            }
            for (j = 0; j < handSize; j++) {
                if (i%6 == 0) {
                    state.hand[i][j] = (rand() % 3) + 4;
                } 
                else {
                    state.hand[i][j] = (rand() % 27);
                }
            }  
            for (j = 0; j < discardPileSize; j++) {
                if (i%6 == 0) {
                    state.discard[i][j] = (rand() % 3) + 4;
                } 
                else {
                    state.discard[i][j] = (rand() % 27);
                }
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
        int k, playCard, preHandCount = 0, postHandCount = 0, preCoinValue = 0, postCoinValue = 0, wasShuffled = 0, preTreasureCount = 0, postTreasureCount = 0, newTreasure = 0, newCard, z = 0;
        int testCurrentPlayer = currentPlayer;
        int temp[MAX_HAND];

        //Figure out what is in the player's hand.
        preHandCount = testState.handCount[testCurrentPlayer];
        preCoinValue = testState.coins;

        for (k = 0; k < preHandCount; k++) {
            if(testState.hand[testCurrentPlayer][k] == copper) {
                preCoinValue += 1;
                preTreasureCount++;
            }
            if (testState.hand[testCurrentPlayer][k] == silver) {
                preCoinValue += 2;
                preTreasureCount++;
            }
            if (testState.hand[testCurrentPlayer][k] == gold) {
                preCoinValue += 3;
                preTreasureCount++;
            }
        }

        //Play Adventurer
        playCard = cardEffect(adventurer, choice1, choice2, choice3, &testState, handPosition, bonus);
        postHandCount = testState.handCount[testCurrentPlayer];
        postCoinValue = testState.coins;

        for (k = 0; k < postHandCount; k++){
            if (testState.hand[testCurrentPlayer][k] == copper) {
                postCoinValue += 1;
                postTreasureCount++;                
            }
            if (testState.hand[testCurrentPlayer][k] == silver) {
                postCoinValue += 2;
                postTreasureCount++;  
            }
            if (testState.hand[testCurrentPlayer][k] == gold) {
                postCoinValue += 3;
                postTreasureCount++;  
            }
        }
        assertTrue(postTreasureCount >= preTreasureCount, "There are fewer treasures after Adventurer than there shoud be.");
        assertTrue(postCoinValue >= preCoinValue, "The value of the coins in hand has gone down.");

        //checks to make sure other player's states haven't changed.
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

        //check to see if the deck is shuffeling.
        while (newTreasure < 2) {
            drawCard(testCurrentPlayer, &testState);
            if (testState.deckCount[testCurrentPlayer] < 1) {
                //printf("PreDraw:, %d\n", testState.deckCount[testCurrentPlayer]);
                drawCard(testCurrentPlayer, &testState);
                assertTrue(testState.deckCount[testCurrentPlayer] >= 0, "The deck should have been shuffled and wasn't.");
                //printf("PostDraw:, %d\n", testState.deckCount[testCurrentPlayer]);
                wasShuffled = 1;
            }
            newCard = testState.hand[testCurrentPlayer][(testState.handCount[testCurrentPlayer])-1];
            if (newCard == copper || newCard == silver || newCard == gold) {
                newTreasure++;
            } 
            else {
                temp[z] = newCard;
                testState.handCount[testCurrentPlayer]--;
                z++;
            }
        }
        //removes the temp hand just like in the Adventurer cardEffect
        while (z-1>=0){
            testState.discard[testCurrentPlayer][testState.discardCount[testCurrentPlayer]++] = temp[z-1];
            z=z-1;
        }
        if (wasShuffled == 0) {
            assertTrue(postHandCount == preHandCount + 2, "The hand size after playing Adventurer has not increased by 2 treasures, and the deck wasn't shuffled.");
        }
    }

    printf("Adventurer finished all the tests!\n");

    return 0;
}