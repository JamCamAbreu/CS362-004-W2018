/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: buyCard
 * Card/Function location: dominon.c
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

const int BUY_CARD = village;

#define LEGAL     0
#define NE_COINS  1
#define E_SUPPLY  2
#define NE_BUYS   3


// -- RESET GAME STATE --
void resetStates(struct gameState* G, int numPlayers) {
    int i;

    // player starts with no cards in deck:
    for (i = 0; i < numPlayers; i++) {
      G->deckCount[i] = 0;
    }
}


void setTestConditions(struct gameState* G, int testType, int cardType, int cardCost, int drawScreen) {
  if (testType == LEGAL) {
    G->coins = cardCost + 2;
    G->numBuys = 1;
    G->supplyCount[cardType] = 20;
    if (drawScreen)
      printf("\tTEST TYPE: LEGAL CONDITIONS\n");
  }
  else if (testType == NE_COINS) {
    G->coins = 0;
    G->numBuys = 1;
    G->supplyCount[cardType] = 20;
    if (drawScreen)
      printf("\tTEST TYPE: not enough coins\n");
  }
  else if (testType == E_SUPPLY) {
    G->coins = cardCost + 2;
    G->numBuys = 1;
    G->supplyCount[cardType] = 0;
    if (drawScreen)
      printf("\tTEST TYPE: empty supply pile\n");
  }
  else if (testType == NE_BUYS) {
    G->coins = cardCost + 2;
    G->numBuys = 0;
    G->supplyCount[cardType] = 20;
    if (drawScreen)
      printf("\tTEST TYPE: not enough buys\n");
  }
  else {
    printf("\tTEST TYPE: ERROR in setTestConditions function, exiting.\n");
    exit(1); // crash test program
  }
}








int main() {

  srand(time(NULL));

  // Basic Game Setup
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
  int dCountBefore, dCountAfter;
  int coinsBefore, coinsAfter;
  int supplyBefore, supplyAfter;
  int buysBefore, buysAfter;
  int returnStat;
  int cardCost = getCost(BUY_CARD);

  if (DISPLAY_TESTS)
    printf("buyCard TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========
  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);

    // -- RESET GAME STATE -- 
    memset(&G, 23, sizeof(struct gameState)); 
    initializeGame(numPlayers, k, seed, &G); 
    resetStates(&G, numPlayers);

    // Set up correct testing conditions:
    setTestConditions(&G, LEGAL, BUY_CARD, cardCost, DISPLAY_TESTS);
    G.whoseTurn = p;

    // Check states before:
    handSizeBefore = G.handCount[p];
    numActionsBefore = G.numActions;
    deckSizeBefore = G.deckCount[p];
    coinsBefore = G.coins;
    dCountBefore = G.discardCount[p];
    supplyBefore = G.supplyCount[BUY_CARD];
    buysBefore = G.numBuys;

    // --- RUN SHUFFLE FUNCTION ---
    returnStat = buyCard(BUY_CARD, &G);

    // Check states AFTER
    handSizeAfter = G.handCount[p];
    numActionsAfter = G.numActions;
    deckSizeAfter = G.deckCount[p];
    coinsAfter = G.coins;
    dCountAfter = G.discardCount[p];
    supplyAfter = G.supplyCount[BUY_CARD];
    buysAfter = G.numBuys;


    // Show results:
    // RETURN STATUS OF FUNCTION
    if (DISPLAY_TESTS)
      printf("\t\tReturn Status of buyCard function: %d\n", returnStat);
    testCondition(returnStat == 0, &fails, DISPLAY_TESTS);
    
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

    // DISCARD SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdiscard pile size before=%d, after=%d\n", 
          dCountBefore, dCountAfter);
    testCondition(dCountAfter == (dCountBefore + 1), &fails, DISPLAY_TESTS);

    // SUPPLY BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tsupply pile size before=%d, after=%d\n", 
          supplyBefore, supplyAfter);
    testCondition(supplyAfter == (supplyBefore - 1), &fails, DISPLAY_TESTS);

    // NUMBER OF BUYS BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tnumber of buys before=%d, after=%d\n", buysBefore, buysAfter);
    testCondition(buysBefore == (buysAfter + 1), &fails, DISPLAY_TESTS);

    // NUMBER OF COINS BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tcard cost: %d; coins before=%d, after=%d\n", 
          cardCost, coinsBefore, coinsAfter);
    testCondition(coinsAfter == (coinsBefore - cardCost), &fails, DISPLAY_TESTS);


    printf("\n");

  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main











