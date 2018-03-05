/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * UNIT TEST FOR DOMINION GAME
 * CS 362-400, Winter 2018
 * ------------------------------
 * Card/Function name: fullDeckCount
 * Card/Function location: dominon.c
 ************************************/

// check:
// 1. amount of cards in deck, including 0 and max
// 2. amount of cards in hand, including 0 and max
// 3. amount of cards in discard pile


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
  const int pickCard = 4; // in this case, the 'mine' card
  int pickCardsDeck, pickCardsHand, pickCardsDiscard; // count of how many
  int totalPickCards; // The three added together
  int sizeDeck, sizeHand, sizeDiscard; // TOTAL, including other cards
  int curCard;
  int randPos;
  int returnCount; // returned count from fullDeckCount function


  // Extra variables:
  int fails = 0; // keep track of how many fails for this program
  int p; // current player

  if (DISPLAY_TESTS)
    printf("fullDeckCount TEST: Begin test\n");

  // ========= TEST CORRECT OUTPUT (DESIRED OUTCOME) =========
  // each player
  for (p = 0; p < numPlayers; p++) {

    if (DISPLAY_TESTS)
      printf("\tPlayer %d:\n", p);

    // -- RESET GAME STATE -- 
    memset(&G, 23, sizeof(struct gameState)); 
    initializeGame(numPlayers, k, seed, &G); 
    G.whoseTurn = p;

    // player starts with no cards in deck, hand, and discard:
    for (i = 0; i < numPlayers; i++) {
      G.deckCount[i] = 0;
      G.handCount[i] = 0;
      G.discardCount[i] = 0;
    }


    // -- Fill with random cards BESIDES the pickCard --
    // DECK
    sizeDeck = rand() % (MAX_DECK - 1);
    for (i = 0; i < sizeDeck; i++) {
      curCard = rand() % 10;
      while (curCard == pickCard) // don't pick pickCard
        curCard = rand() % 10;
      G.deck[p][G.deckCount[p]] = k[curCard]; // append
      G.deckCount[p]++;
    }

    // HAND
    sizeHand = rand() % (MAX_HAND - 1);
    for (i = 0; i < sizeHand; i++) {
      curCard = rand() % 10;
      while (curCard == pickCard)
        curCard = rand() % 10;
      G.hand[p][i] = k[curCard];
      G.handCount[p]++;
    }

    // DISCARD
    sizeDiscard = rand() % (MAX_DECK - 1);
    for (i = 0; i < sizeDiscard; i++) {
      curCard = rand() % 10;
      while (curCard == pickCard)
        curCard = rand() % 10;
      G.discard[p][i] = k[curCard];
      G.discardCount[p]++;
    }


    // -- REPLACE CARDS with a controlled amount pickCards --
    // DECK
    pickCardsDeck = rand() % (sizeDeck/2);
    for (i = 0; i < pickCardsDeck; i++) {
      randPos = rand() % (sizeDeck - 1);
      curCard = G.deck[p][randPos];
      while (curCard == k[pickCard]) {
        randPos = rand() % (sizeDeck - 1);
        curCard = G.deck[p][randPos];
      }
      G.deck[p][randPos] = k[pickCard]; // replace
    }

    // HAND
    pickCardsHand = rand() % (sizeHand/2);
    for (i = 0; i < pickCardsHand; i++) {
      randPos = rand() % (sizeHand - 1);
      curCard = G.hand[p][randPos];
      while (curCard == k[pickCard]) {
        randPos = rand() % (sizeHand - 1);
        curCard = G.hand[p][randPos];
      }
      G.hand[p][randPos] = k[pickCard]; // replace
    }

    // DISCARD
    pickCardsDiscard = rand() % (sizeDiscard/2);
    for (i = 0; i < pickCardsDiscard; i++) {
      randPos = rand() % (sizeDiscard - 1);
      curCard = G.discard[p][randPos];
      while (curCard == k[pickCard]) {
        randPos = rand() % (sizeDiscard - 1);
        curCard = G.discard[p][randPos];
      }
      G.discard[p][randPos] = k[pickCard]; // replace
    }
    
    
    // Check states before:
    handSizeBefore = G.handCount[p];
    deckSizeBefore = G.deckCount[p];
    discardBefore = G.discardCount[p];

    // --- RUN fullDeckCount FUNCTION ---
    returnCount = fullDeckCount(p, k[pickCard], &G);

    // Check states AFTER
    handSizeAfter = G.handCount[p];
    deckSizeAfter = G.deckCount[p];
    discardAfter = G.discardCount[p];


    // Show results:
    
    // CORRECT NUMBER OF CARDS COUNTED:
    totalPickCards = pickCardsDeck + pickCardsHand + pickCardsDiscard;
    if (DISPLAY_TESTS)
      printf("\t\tActual amount of cards=%d, counted=%d\n", 
          totalPickCards, returnCount);
    testCondition(totalPickCards == returnCount, &fails, DISPLAY_TESTS);

    // HAND SIZE
    if (DISPLAY_TESTS)
      printf("\t\thandSize before=%d, after=%d\n", handSizeBefore, handSizeAfter);
    testCondition(handSizeBefore == handSizeAfter, &fails, DISPLAY_TESTS);

    // DECK SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdeck size before=%d, after=%d\n", deckSizeBefore, deckSizeAfter);
    testCondition(deckSizeBefore == deckSizeAfter, &fails, DISPLAY_TESTS);

    // DISCARD SIZES BEFORE AND AFTER
    if (DISPLAY_TESTS)
      printf("\t\tdiscard pile size before=%d, after=%d\n", 
          discardBefore, discardAfter);
    testCondition(discardBefore == discardAfter, &fails, DISPLAY_TESTS);

    printf("\n");

  } // end for each player


  // Display Final Test Results
  displayTestResults(&fails);

  return 0;
} // end main













