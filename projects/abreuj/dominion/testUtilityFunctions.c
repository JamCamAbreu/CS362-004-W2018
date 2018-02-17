/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * My own functions to help with unit testing
 * for the dominion c code. 
 * CS 362-400, Winter 2018
 ************************************/

#include "testUtilityFunctions.h"


// CHECK h FILE FOR COLOR SWITCH, default = off

void testCondition(int condition, int* fails, int display) {

  if (condition) {
    if (display == 1) {
      printf(GREEN "\t\t\t[STATUS: PASS]\n\n" RESET);
    }
  }
  else {
    if (display == 1)
      printf(RED "\t\t\t[STATUS: FAIL]\n\n" RESET);

    (*fails)++;
  }
}



void displayTestResults(int* fails) {
  printf(YELLOW "RESULTS: " RESET);
  if (*fails > 0)
    printf(RED "FAILURE. Total test fails: %d" RESET, *fails);
  else
    printf(GREEN "SUCCESS. All tests pass" RESET);
}

