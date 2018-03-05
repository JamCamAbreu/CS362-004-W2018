/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: Outpost Card (outpostEffect)
 * Card/Function location: dominon.c
 *
 * Make Command:
 * cardtest4: dominion.o cardtest4.c
 *    gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
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

const int TEST_CARD_ID = outpost;

int main() {

  // Basic Game Setup
  int i, gameStateStatus;
  int seed = 1234;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, outpost, great_hall};
  struct gameState G;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player
  int cardLoc = 0; // outpost card will be located in hand position 0 on first pass
  int pTop; // the type of card that is on the top of the played pile
  int handSizeBefore, handSizeAfter;
  int numActionsBefore, numActionsAfter;
  int numPlayedCards;

  if (DISPLAY_TESTS)
    printf("OUTPOST TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========

  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);


    // Place the card in each posible hand position
    for (cardLoc = 0; cardLoc < 5; cardLoc++) {

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

      // Put 
      G.hand[p][cardLoc] = TEST_CARD_ID;

      // clear used cards:
      G.playedCardCount = 0;

      // -- FINISHED RESET --

      // Check states before:
      handSizeBefore = G.handCount[p];
      numActionsBefore = G.numActions;
      numPlayedCards = G.playedCardCount;

      // --- RUN OUTPOST EFFECT ---
      outpostEffect(&G, p, cardLoc);
      G.numActions--;

      // Check states AFTER
      handSizeAfter = G.handCount[p];
      numActionsAfter = G.numActions;
      numPlayedCards = G.playedCardCount;
      pTop = G.playedCards[numPlayedCards - 1];


      // DEBUG
      /*
      printf("playedCards:");
      for (i = 0; i < G.playedCardCount; i++) {
        printf(" %d", G.playedCards[i]);
      }
      printf(", Retrieved: %d", pTop);
      printf("\n");
      */

      // Show results:
      // HAND SIZE
      if (DISPLAY_TESTS)
        printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
      testCondition(handSizeBefore == (handSizeAfter + 1), &fails, DISPLAY_TESTS);

      // NUMBER OF ACTIONS
      if (DISPLAY_TESTS)
        printf("\t\tactions before=%d, after=%d\n", numActionsBefore, numActionsAfter);
      testCondition(numActionsBefore == (numActionsAfter + 1), &fails, DISPLAY_TESTS);

      // WHICH CARD DISCARDED
      if (DISPLAY_TESTS)
        printf("\t\tlast played card=%d, outpostID=%d\n", pTop, TEST_CARD_ID);
      testCondition(pTop == TEST_CARD_ID, &fails, DISPLAY_TESTS);

      // STATUS FROM initializeGame FUNCTION:
      if (DISPLAY_TESTS)
        printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
      testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);

      printf("\n");
    } // end for each hand position


  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main









