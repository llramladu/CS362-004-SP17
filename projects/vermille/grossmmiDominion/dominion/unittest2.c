//Unit test for updateCoins function
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
        printf ("UPDATE COINS ASSERT NOT TRUE: %s\n", error);
        exit(0);
    }
    return 0;
}

int main (int argc, char** argv) {
    struct gameState state;

    int kingdom[10] = {adventurer, cutpurse, gardens, great_hall, mine, minion, sea_hag, smithy, tribute, village};
    
    int i, j, players, seed, currentPlayerCardCount, qtyCopper, qtySilver, qtyGold, bonus, coinValueTotal;
    
    for (i = 0; i < MAX_TESTS; i++) {
        players = rand() % 4;
        seed = (rand() % 123456780) + 1;

        initializeGame(players, kingdom, seed, &state);
        
        currentPlayerCardCount = state.handCount[0];
        qtyCopper = 0;
        qtySilver = 0;
        qtyGold = 0;
        bonus = rand() % currentPlayerCardCount;

        //count how many of each coin type are in the player's hand
        for (j = 0; j < currentPlayerCardCount; j++) {

            if (state.hand[0][j] == copper) {
        	   qtyCopper++;
            }
            else if (state.hand[0][j] == silver) {
        	   qtySilver++;
            }
            else if (state.hand[0][j] == gold) {
        	   qtyGold++;
            }
        }
        //calculate total value of the coins
        coinValueTotal = (qtyCopper * 1) + (qtySilver * 2) + (qtyGold * 3) + bonus;
        //call updateCoins function
        updateCoins(0, &state, bonus);
        //check against calculated number of coins
        assertTrue(state.coins == coinValueTotal, "The value of the coins is not matching.");
    }
    printf("Unit Test on updateCoins passed!\n");
    return 0;
}