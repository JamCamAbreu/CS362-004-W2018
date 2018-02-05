/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Function name: shuffle
 * Function location: dominon.c
 ************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h> // used for random testing
#include <stdlib.h> // used for random testing
#include "rngs.h"
#include "testUtilityFunctions.h"

// Displays Tests and results. Set to 0 for off, any number for on
const int DISPLAY_TESTS = 1;


int main() {

  srand(time(NULL));

  // Basic Game Setup
  int i, gameStateStatus;
  int seed = 123;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, outpost, great_hall};
  struct gameState G;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player
  int handSizeBefore, handSizeAfter;
  int numActionsBefore, numActionsAfter;
  int deckSizeBefore, deckSizeAfter;
  int tempDeck[MAX_DECK]; // used to check if deck actually changed
  int differentDeck = 0; // 0 indicates false, 1 true
  int cardPrev, cardNow; // compare temp deck to now deck
  int kCard; // used to add random cards to deck
  int numCardsAdd;

  if (DISPLAY_TESTS)
    printf("SHUFFLE TEST: Begin test\n");

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

    // player starts with no cards in deck:
    G.deckCount[p] = 0;

    // reset tempDeck
    for (i = 0; i < MAX_DECK; i++)
      tempDeck[i] = -1;

    // -- FINISHED RESET --


    // ADD RANDOM CARDS TO DECK:
    numCardsAdd = rand() % (MAX_DECK - 1);
    for (i = 0; i < numCardsAdd; i++) {
      kCard = rand() % 10; // get a random k card from our k array
      G.deck[p][G.deckCount[p]] = k[kCard];
      G.deckCount[p]++;
    }


    // Check states before:
    handSizeBefore = G.handCount[p];
    numActionsBefore = G.numActions;
    deckSizeBefore = G.deckCount[p];

    // copy deck to temp deck:
    for (i = 0; i < G.deckCount[p]; i++) {
      tempDeck[i] = G.deck[p][i];
    }

    // --- RUN SHUFFLE FUNCTION ---
    shuffle(p, &G);

    // Check states AFTER
    handSizeAfter = G.handCount[p];
    numActionsAfter = G.numActions;
    deckSizeAfter = G.deckCount[p];

    // compare shuffled cards to previous deck:
    differentDeck = 0; // false until proven true
    for (i = 0; i < G.deckCount[p]; i++) {
      cardPrev = tempDeck[i];
      cardNow = G.deck[p][i];
      if (cardPrev != cardNow)
        differentDeck = 1; // no longer the same, proven false
    }

    // Show results:
    // HAND SIZE
    if (DISPLAY_TESTS)
      printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
    testCondition(handSizeBefore == handSizeAfter, &fails, DISPLAY_TESTS);

    // NUMBER OF ACTIONS
    if (DISPLAY_TESTS)
      printf("\t\tactions before=%d, after=%d\n", numActionsBefore, numActionsAfter);
    testCondition(numActionsBefore == numActionsAfter, &fails, DISPLAY_TESTS);

    // DECK SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdeck size before=%d, after=%d\n", deckSizeBefore, deckSizeAfter);
    testCondition(deckSizeBefore == deckSizeAfter, &fails, DISPLAY_TESTS);

    // Check to see if the decks are different
    if (DISPLAY_TESTS)
      printf("\t\tDecks the same? %d (1=different)\n", differentDeck);
    testCondition(differentDeck == 1, &fails, DISPLAY_TESTS);

    // STATUS FROM initializeGame FUNCTION:
    if (DISPLAY_TESTS)
      printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
    testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);

    printf("\n");

  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main










