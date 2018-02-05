/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: village (villageEffect)
 * Card/Function location: dominon.c
 *
 * Make Command:
 * cardtest3: dominion.o cardtest3.c
 *    gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
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
  int handSizeBefore, handSizeAfter;
  int numActionsBefore, numActionsAfter;
  int villageLoc = 0; // village will be located in hand position 0

  if (DISPLAY_TESTS)
    printf("SMITHY TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========

  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);


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
    G.hand[p][villageLoc] = village;
    // -- FINISHED RESET --


    // Check states before:
    handSizeBefore = G.handCount[p];
    numActionsBefore = G.numActions;

    // --- RUN VILLAGE EFFECT ---
    villageEffect(p, &G, villageLoc);
    G.numActions--;

    // Check states AFTER
    handSizeAfter = G.handCount[p];
    numActionsAfter = G.numActions;

    // Show results:
    if (DISPLAY_TESTS)
      printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
    testCondition(handSizeBefore == handSizeAfter, &fails, DISPLAY_TESTS);

    if (DISPLAY_TESTS)
      printf("\t\tactions before=%d, after=%d\n", numActionsBefore, numActionsAfter);
    testCondition(numActionsBefore == (numActionsAfter - 1), &fails, DISPLAY_TESTS);

    // STATUS FROM initializeGame FUNCTION:
    if (DISPLAY_TESTS)
      printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
    testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);

  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main







