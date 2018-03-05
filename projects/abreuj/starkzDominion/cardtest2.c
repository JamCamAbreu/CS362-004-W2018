
/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: adventurer (adventurerEffect)
 * Card/Function location: dominon.c
 *
 * Make Command:
 * cardtest2: dominion.o cardtest2.c
 *    gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
 ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "testUtilityFunctions.h"

// Displays Tests and results. Set to 0 for off, any number for on
const int DISPLAY_TESTS = 1;


int main() {

  // Basic Game Setup
  int i, gameStateStatus;
  int seed = 1234;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, baron, great_hall};
  struct gameState G;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player
  int st; // the number of treasures the player started with
  int adventurerLoc = 0; // the hand location of the adventurer card
  int temphand[MAX_HAND]; // used to store cards that will be discarded
  int tempCount; // NUMBER of cards that will be discarded

  printf("ADVENTURER TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========

  // each player
  for (p = 0; p < numPlayers; p++) {

    // ----- TEST CORRECT AMOUNT OF TREASURE CARDS ARE DRAWN -----
    // increment the amount of starting hand treasures (besides the adventurer
    // card)
    int numTBefore, numTAfter;
    int curCard;
    printf("\tPlayer %d:\n", p);
    for (st = 0; st <= 4; st++) {



      // -- RESET GAME STATE --
      // clear game state
      memset(&G, 23, sizeof(struct gameState)); 
      // Note: 23 is the code for End Transmission Block, check wikipedia

      // initialize new game
      gameStateStatus = initializeGame(numPlayers, k, seed, &G); 

      // clear cards:
      for (i = 0; i < MAX_HAND; i++)
        G.hand[p][i] = 0;

      G.handCount[p] = 0;

      // fill hand with dummy cards
      for (i = 0; i < 5; i++) {
        G.hand[p][i] = estate;
        G.handCount[p]++;
      }

      // Replace first card in players hand with an adventurer card
      G.hand[p][adventurerLoc] = adventurer;


      // -- BEGIN VARIANCE -- 
      // replace dummy cards with starting treasure cards (coppers)
      int j;
      for (j = 0; j < st; j++) // at most 3
        G.hand[p][1 + j] = copper;  // at most modifies position 4

      // count treasure cards in current hand BEFORE adventurer card effect
      numTBefore = 0;
      for (j = 0; j < G.handCount[p]; j++) {
        curCard = G.hand[p][j];
        if (curCard == copper || curCard == silver || curCard == gold)
          numTBefore++;
      }

      // Make sure above code works:
      if (DISPLAY_TESTS)
        printf("\t\tstartingTreasures=%d, BEFOREeffect=%d, ", st, numTBefore);

      // RESET the temp cards:
      for (j = 0; j < MAX_HAND; j++)
        temphand[MAX_HAND] = 0;
      tempCount = 0;

      // Test the effect here:
      //adventurerEffect(numTBefore, &G, p, 0, temphand, tempCount);
      playAdventurer(&G, p, 0);
      G.numActions--;

      // count treasure cards in current hand AFTER adventurer card effect
      numTAfter = 0;
      for (j = 0; j < G.handCount[p]; j++) {
        curCard = G.hand[p][j];
        if (curCard == copper || curCard == silver || curCard == gold)
          numTAfter++;
      }


      // - results here -
      if (DISPLAY_TESTS)
        printf("AFTEReffect=%d\n", numTAfter);

      // Only applies if the number of treasures held were already less than 2
      if (numTBefore < 2)
        testCondition(numTAfter == 2, &fails, DISPLAY_TESTS);
      else {
        if (DISPLAY_TESTS)
          printf("\t\t\t[STATUS: NULL TEST: starting treasures >= 2]\n");
      }
    } // end for starting treasure card count


    // STATUS FROM initializeGame FUNCTION:
    if (DISPLAY_TESTS)
      printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
    testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);


    if (DISPLAY_TESTS)
      printf("\n");
  } // end for each player


  
  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main





