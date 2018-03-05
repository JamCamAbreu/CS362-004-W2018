/*************************************
 * Author: James Cameron Abreu
 * Date: 02/08/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: great_hall (great_hallEffect)
 * Card/Function location: dominon.c
 ************************************/


// Great Hall is suppose to:
// 1. +1 card
// 2. +1 action
// 3. discard gHall card

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>     // used for floor function

#include <stdlib.h>   // used in argv convert to int
#include <inttypes.h> // used in argv convert to int
#include <errno.h>    // used in argv convert to int
#include <string.h>   // used in argv convert to int

#include "rngs.h"
#include "testUtilityFunctions.h"


// Displays Tests and results. Set to 0 for off, any number for on
// 0:   off
// 1:   display all tests
// 2:   display bad tests only
const int DISPLAY_TESTS = 2;

const int DEFAULT_SEED = 1234;
const int MAX_STARTING_HAND_SIZE = 30;  // realistic max number of hand size
const int MAX_STARTING_NUM_ACTIONS = 20;
const int NUM_PLAYERS = 2;
const int NUM_K_CARDS = 10;


int main(int argc, char* argv[]) {


  // ====== SET UP TEST SEED ==============
  int seed;
  if (argc > 1) {
    // first convert the arg into an int:
    intmax_t num = strtoimax(argv[1], NULL, 10);
    if (num == INTMAX_MAX && errno == ERANGE) {
      seed = DEFAULT_SEED;
      if (DISPLAY_TESTS == 1)
        printf("Warning: given seed exceeds INTMAX_MAX. Using default seed.\n");
    }
    else {
      seed = (int)num;
    }
  }
  else {
    seed = DEFAULT_SEED;
    if (DISPLAY_TESTS == 1)
      printf("Warning: No seed supplied in arg[1]. Using default seed.\n");
  }

  // plant the random seed:
  SelectStream(1);
  PutSeed((long)seed);

  if (DISPLAY_TESTS == 1)
    printf("Great Hall RANDOM TEST: Begin test with seed=%d\n", seed);





  // ===== BASIC GAME SETUP =====
  int i, gameStateStatus;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, baron, great_hall};
  struct gameState G;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player
  int ghLoc = 0; // the hand location of the adventurer card
  int stHandNum;
  int stActionsNum;

  // variables for testing:
  int handSizeBefore, handSizeAfter;
  int deckSizeBefore, deckSizeAfter;
  int discardBefore, discardAfter;
  int playedBefore, playedAfter;
  int numActionsBefore, numActionsAfter;





  // ===== CONFIGURE RANDOM GAME STATE =====
  // randomize which player used (player 1 or 2)
  p = floor(Random() * NUM_PLAYERS);

  // randomize hand size and number of actions:
  stHandNum = floor(Random() * MAX_STARTING_HAND_SIZE);
  stActionsNum = floor(Random() * MAX_STARTING_NUM_ACTIONS);


  // -- RESET GAME STATE --
  // clear game state
  memset(&G, 23, sizeof(struct gameState)); 
  // Note: 23 is the code for End Transmission Block, check wikipedia

  // initialize new game
  gameStateStatus = initializeGame(NUM_PLAYERS, k, seed, &G); 

  // clear cards:
  for (i = 0; i < MAX_HAND; i++)
    G.hand[p][i] = 0;
  G.handCount[p] = 0;

  // fill hand with random cards
  int pick;
  for (i = 0; i < stHandNum; i++) {
    pick = floor(Random() * NUM_K_CARDS + 3);
    if (pick < NUM_K_CARDS) { // give random kingdom card
      G.hand[p][i] = k[pick];
    } else if (pick == NUM_K_CARDS + 1) { // copper
      G.hand[p][i] = copper;
    } else if (pick == NUM_K_CARDS + 2) { // silver
      G.hand[p][i] = silver;
    } else if (pick == NUM_K_CARDS + 3) { // gold
      G.hand[p][i] = gold;
    } else {G.hand[p][i] = estate; }      // estate
    G.handCount[p]++;
  }

  // Replace first card in players hand with a great hall card
  G.hand[p][ghLoc] = great_hall;

  // Set the number of actions to start the round:
  stActionsNum = floor(Random() * MAX_STARTING_NUM_ACTIONS);
  G.numActions = stActionsNum;

  // ====== BEFORE PLAYING CARD =======
  handSizeBefore = G.handCount[p];
  deckSizeBefore = G.deckCount[p];
  discardBefore = G.discardCount[p];
  playedBefore = G.playedCardCount;
  numActionsBefore = G.numActions;

  // ====== PLAY THE CARD ============
  great_hallEffect(&G, p, ghLoc);
  G.numActions--; // for the gHall card

  // ======= AFTER PLAYING CARD =======
  handSizeAfter = G.handCount[p];
  deckSizeAfter = G.deckCount[p];
  discardAfter = G.discardCount[p];
  playedAfter = G.playedCardCount;
  numActionsAfter = G.numActions;


  // ======= INDIVIDUAL TESTS ==========
  // HAND SIZE BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
  testCondition(handSizeAfter == handSizeBefore, &fails, DISPLAY_TESTS);

  // DECK SIZES BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tdeck size before=%d, after=%d\n", deckSizeBefore, deckSizeAfter);
  testCondition(deckSizeAfter == (deckSizeBefore - 1), &fails, DISPLAY_TESTS);

  // DISCARD SIZES BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tdiscard pile size before=%d, after=%d\n", 
        discardBefore, discardAfter);
  testCondition(discardBefore == discardAfter, &fails, DISPLAY_TESTS);

  // PLAYED SIZES BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tPlayed pile size before=%d, after=%d\n", 
        playedBefore, playedAfter);
  testCondition(playedAfter == (playedBefore + 1), &fails, DISPLAY_TESTS);

  // NUMBER OF ACTIONS BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tNumber of actions before=%d, after=%d\n", 
        numActionsBefore, numActionsAfter);
  testCondition(numActionsAfter == numActionsBefore, &fails, DISPLAY_TESTS);

  // STATUS FROM initializeGame FUNCTION:
  if (DISPLAY_TESTS == 1)
    printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
  testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS);







  // ======= FINAL TEST RESULTS ===========
  if (DISPLAY_TESTS == 1)
    printf("\n");
  
  // normal results
  if (DISPLAY_TESTS == 1) {
    displayTestResults(&fails);
    printf(", seed: %d\n", seed);
  }

  // Only show when failed, meant to be piped to file in makefile:
  else if (DISPLAY_TESTS == 2)
    if ((fails) > 0) {
      displayTestResults(&fails);
      printf(", seed: %d\n", seed);
    }

  return 0;
} // end main


