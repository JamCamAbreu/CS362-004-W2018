/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: discardCard
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


int main() {

  srand(time(NULL));

  // Basic Game Setup
  int i;
  int seed = 123;
  int numPlayers = 2;
  int k[10] = {adventurer, council_room, feast, gardens, mine, 
               remodel, smithy, village, outpost, great_hall};
  struct gameState G;

  // Important Variables:
  int handSizeBefore, handSizeAfter;
  int deckSizeBefore, deckSizeAfter;
  int discardBefore, discardAfter;
  int playedBefore, playedAfter;
  int sizeDeck, sizeHand, sizeDiscard; // TOTAL, including other cards

  // for comparing before and after the discard
  int randHandPos; 
  int pickCard; // determined by randHandPos
  int pickCardHandBefore, pickCardHandAfter;
  int pickCardPlayedBefore, pickCardPlayedAfter;
  int curCard;

  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player

  if (DISPLAY_TESTS)
    printf("discardCard TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========
  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);

    // -- RESET GAME STATE -- 
    memset(&G, 23, sizeof(struct gameState)); 
    initializeGame(numPlayers, k, seed, &G); 
    G.whoseTurn = p;

    // player starts with no cards in deck, hand, played, and discard:
    for (i = 0; i < numPlayers; i++) {
      G.deckCount[i] = 0;
      G.handCount[i] = 0;
      G.discardCount[i] = 0;
      G.playedCardCount = 0;
    }

    // -- Fill with random cards BESIDES the pickCard --
    // DECK
    sizeDeck = rand() % (MAX_DECK - 1);
    for (i = 0; i < sizeDeck; i++) {
      curCard = rand() % 10;
      G.deck[p][G.deckCount[p]] = k[curCard]; // append
      G.deckCount[p]++;
    }

    // HAND
    sizeHand = rand() % (MAX_HAND - 1);
    for (i = 0; i < sizeHand; i++) {
      curCard = rand() % 10;
      G.hand[p][i] = k[curCard];
      G.handCount[p]++;
    }

    // DISCARD
    sizeDiscard = rand() % (MAX_DECK - 1);
    for (i = 0; i < sizeDiscard; i++) {
      curCard = rand() % 10;
      G.discard[p][i] = k[curCard];
      G.discardCount[p]++;
    }




   
    
    // Check states before:
    handSizeBefore = G.handCount[p];
    deckSizeBefore = G.deckCount[p];
    discardBefore = G.discardCount[p];
    playedBefore = G.playedCardCount;

    // pick a random card to discard:
    randHandPos = rand() % (sizeHand - 1);
    pickCard = G.hand[p][randHandPos];
    
    // How many of that card exists... 
    // IN HAND:
    pickCardHandBefore = 0;
    for (i = 0; i < G.handCount[p]; i++) {
      curCard = G.hand[p][i];
      if (curCard == pickCard)
        pickCardHandBefore++;
    }

    // IN PLAYED:
    pickCardPlayedBefore = 0;
    for (i = 0; i < G.playedCardCount; i++) {
      curCard = G.playedCards[i];
      if (curCard == pickCard)
        pickCardPlayedBefore++;
    }

    // --- RUN discardCard FUNCTION ---
    discardCard(randHandPos, p, &G, 0); // don't trash

    // Check states AFTER
    handSizeAfter = G.handCount[p];
    deckSizeAfter = G.deckCount[p];
    discardAfter = G.discardCount[p];
    playedAfter = G.playedCardCount;

    // How many of that card exists... 
    // IN HAND:
    pickCardHandAfter = 0;
    for (i = 0; i < G.handCount[p]; i++) {
      curCard = G.hand[p][i];
      if (curCard == pickCard)
        pickCardHandAfter++;
    }

    // IN PLAYED:
    pickCardPlayedAfter = 0;
    for (i = 0; i < G.playedCardCount; i++) {
      curCard = G.playedCards[i];
      if (curCard == pickCard)
        pickCardPlayedAfter++;
    }


    // Show results:
    

    // CARD CHOSEN:
    if (DISPLAY_TESTS)
      printf("\t\tPicked Card: %d\n", pickCard);

    // PICKED CARDS HAND BEFORE AND AFTER:
    if (DISPLAY_TESTS)
      printf("\t\tNum of card hand before=%d, after=%d\n", 
          pickCardHandBefore, pickCardHandAfter);
    testCondition(pickCardHandAfter == (pickCardHandBefore - 1), &fails, DISPLAY_TESTS);

    // PICKED CARDS PLAYED BEFORE AND AFTER:
    if (DISPLAY_TESTS)
      printf("\t\tNum of card played pile before=%d, after=%d\n", 
          pickCardPlayedBefore, pickCardPlayedAfter);
    testCondition(pickCardPlayedAfter == (pickCardPlayedBefore + 1), &fails, DISPLAY_TESTS);

    // HAND SIZE BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
    testCondition(handSizeAfter == (handSizeBefore - 1), &fails, DISPLAY_TESTS);

    // DECK SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdeck size before=%d, after=%d\n", deckSizeBefore, deckSizeAfter);
    testCondition(deckSizeBefore == deckSizeAfter, &fails, DISPLAY_TESTS);

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

    printf("\n");

  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main


