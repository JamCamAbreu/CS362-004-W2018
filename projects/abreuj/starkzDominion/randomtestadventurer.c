/*************************************
 * Author: James Cameron Abreu
 * Date: 02/08/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: adventurer (adventurerEffect)
 * Card/Function location: dominon.c
 ************************************/

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
const int MAX_STARTING_TREASURES = 4;
const int NUM_PLAYERS = 2;


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
    printf("ADVENTURER RANDOM TEST: Begin test with seed=%d\n", seed);




  // ===== BASIC GAME SETUP =====
  int i, gameStateStatus;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, baron, great_hall};
  struct gameState G;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player
  int st; // the number of treasures the player started with in hand
  int adventurerLoc = 0; // the hand location of the adventurer card
  int temphand[MAX_HAND]; // used to store cards that will be discarded
  int tempCount; // NUMBER of cards that will be discarded

  // variables for testing:
  int discardBefore, discardAfter;
  int playedBefore, playedAfter;
  int numActionsBefore, numActionsAfter;




  // ===== CONFIGURE RANDOM GAME STATE =====
  // randomize which player used (player 1 or 2)
  p = floor(Random() * NUM_PLAYERS);

  // increment the amount of starting hand treasures (besides the adventurer
  // card)
  int numTBefore, numTAfter;
  int curCard;

  // starting amount of treasure cards in hand
  st = floor(Random() * MAX_STARTING_TREASURES);

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

  // fill hand with dummy 5 cards
  for (i = 0; i < 5; i++) {
    G.hand[p][i] = estate;
    G.handCount[p]++;
  }

  // Replace first card in players hand with an adventurer card
  G.hand[p][adventurerLoc] = adventurer;

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

  // RESET the temp cards (needed for adventurer card)
  for (j = 0; j < MAX_HAND; j++)
    temphand[MAX_HAND] = 0;
  tempCount = 0;

  // ====== BEFORE PLAYING CARD =======
  discardBefore = G.discardCount[p];
  playedBefore = G.playedCardCount;
  numActionsBefore = G.numActions;

  // ====== PLAY THE CARD ============
  //adventurerEffect(numTBefore, &G, p, 0, temphand, tempCount);
  playAdventurer(&G, p, 0);
  
  G.numActions--;

  // ======= AFTER PLAYING CARD =======
  discardAfter = G.discardCount[p];
  playedAfter = G.playedCardCount;
  numActionsAfter = G.numActions;

  // count treasure cards in current hand AFTER adventurer card effect
  numTAfter = 0;
  for (j = 0; j < G.handCount[p]; j++) {
    curCard = G.hand[p][j];
    if (curCard == copper || curCard == silver || curCard == gold)
      numTAfter++;
  }





  // ======= INDIVIDUAL TESTS ==========
  // ----- TEST CORRECT AMOUNT OF TREASURE CARDS ARE DRAWN -----
  if (DISPLAY_TESTS == 1)
    printf("\t\tNumber of Treasures in hand before=%d, after=%d\n", 
        numTBefore, numTAfter);
  if (numTBefore < 2) {
    // If the number of treasures held were already less than 2:
    testCondition(numTAfter == 2, &fails, DISPLAY_TESTS == 1);
  }
  else {
    // Make sure there was no change in treasure card amount:
    testCondition(numTAfter == st, &fails, DISPLAY_TESTS == 1);
  }

  // DISCARD SIZES BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tdiscard pile size before=%d, after=%d\n", 
        discardBefore, discardAfter);
  testCondition(discardBefore == discardAfter, &fails, DISPLAY_TESTS);

  // PLAYED SIZES BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tPlayed pile size before=%d, after=%d\n", 
        playedBefore, playedAfter);
  testCondition(playedAfter == (playedBefore), &fails, DISPLAY_TESTS);

  // NUMBER OF ACTIONS BEFORE AND AFTER
  if (DISPLAY_TESTS == 1)
    printf("\t\tNumber of actions before=%d, after=%d\n", 
        numActionsBefore, numActionsAfter);
  testCondition(numActionsAfter == (numActionsBefore - 1), &fails, DISPLAY_TESTS);

  // STATUS FROM initializeGame FUNCTION:
  if (DISPLAY_TESTS == 1)
    printf("\t\tinitializeGame return value=%d (should be 0)\n", gameStateStatus);
  testCondition(gameStateStatus == 0, &fails, DISPLAY_TESTS == 1);






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


