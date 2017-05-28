#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

//implementation for Village card from Assignment 2
int main()
{
  srand(time(NULL));

  //card set from testDrawCard.c
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState test, control;
  int i, n, r, p, deckCount, discardCount, handCount, playerCount, seed, player;
  //when possible use defined values from dominion.h

  for (i = 0; i < 500; i++)
  {
    playerCount = rand() % (MAX_PLAYERS - 1) + 2;
    player = rand() % playerCount + 1;
    test.deckCount[p] = floor(Random() * MAX_DECK);
    test.discardCount[p] = floor(Random() * MAX_DECK);
    test.handCount[p] = floor(Random() * MAX_HAND);
    seed = rand() % 500;
    initializeGame(playerCount, k, seed, &test);

    shuffle(player, &test);
    gainCard(adventurer, &test, 2, player);
    handCount = test.handCount[player];
    deckCount = test.deckCount[player];
    test.playedCardCount = 0;
    int numActions = test.numActions;
    adventurerM(player, test.hand[player][test.handCount[player] - 1], &test);
    if (test.playedCardCount != 1)
    {
      printf("Error, more than 1 card played for Adventurer\n");
    }
    //grab top card from deck and check it and next card to be valid treasure
    int cardDrawn = test.hand[player][test.handCount[player] - 1];
    if (cardDrawn != copper && cardDrawn != silver && cardDrawn != gold)
    {
      printf("Error. Card drawn after playing Advernturer was not treasure.\n");
    }


  }

  return 0;
}
