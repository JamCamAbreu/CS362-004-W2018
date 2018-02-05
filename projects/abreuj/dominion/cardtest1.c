/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: smithy (smithyEffect)
 * Card/Function location: dominon.c
 *
 * Make Command:
 * cardtest1: dominion.o cardtest1.c
 *    gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
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

  // Important Variables:
  int handSizeBefore, handSizeAfter;
  int deckSizeBefore, deckSizeAfter;
  int discardBefore, discardAfter;
  int playedBefore, playedAfter;
  const int smithyLocation = 0; // smithy will be located in hand position 0

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player

  if (DISPLAY_TESTS)
    printf("SMITHY TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========

  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);

    // -- RESET GAME STATE -- 
    memset(&G, 23, sizeof(struct gameState)); 
    gameStateStatus = initializeGame(numPlayers, k, seed, &G); 

    // clear cards:
    for (i = 0; i < MAX_HAND; i++)
      G.hand[p][i] = 0;
    G.handCount[p] = 0;

    // fill hand with coppers
    for (i = 0; i < 5; i++) {
      G.hand[p][i] = copper;
      G.handCount[p]++;
    }

    // Replace first card in players hand with smithy:
    G.hand[p][smithyLocation] = smithy;



    // Check states before:
    handSizeBefore = G.handCount[p];
    deckSizeBefore = G.deckCount[p];
    discardBefore = G.discardCount[p];
    playedBefore = G.playedCardCount;

    // --- RUN SMITHY EFFECT ---
    smithyEffect(p, &G, smithyLocation);
    G.numActions--; // usually done in game after calling cardEffect
    
    // Check states AFTER
    handSizeAfter = G.handCount[p];
    deckSizeAfter = G.deckCount[p];
    discardAfter = G.discardCount[p];
    playedAfter = G.playedCardCount;




    // Show results:
    // HAND SIZE BEFORE AND AFTER:
    if (DISPLAY_TESTS)
      printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
    testCondition(handSizeBefore == (handSizeAfter - 2), &fails, DISPLAY_TESTS);

    // STATUS FROM initializeGame FUNCTION:
    if (DISPLAY_TESTS)
      printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
    testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);

    // DECK SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdeck size before=%d, after=%d\n", deckSizeBefore, deckSizeAfter);
    testCondition(deckSizeAfter == (deckSizeBefore - 3), &fails, DISPLAY_TESTS);

    // DISCARD SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdiscard pile size before=%d, after=%d\n", 
          discardBefore, discardAfter);
    testCondition(discardBefore == discardAfter, &fails, DISPLAY_TESTS);

    // PLAYED SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tPlayed pile size before=%d, after=%d\n", 
          playedBefore, playedAfter);
    testCondition(playedAfter == (playedBefore + 1), &fails, DISPLAY_TESTS);

  } // end for each player


  

  // Display Final Test Results
  displayTestResults(&fails);


  return 0;
} // end main





