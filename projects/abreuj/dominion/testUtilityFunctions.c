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
    if (display) {
      printf(GREEN "\t\t\t[STATUS: PASS]\n" RESET);
    }
  }
  else {
    if (display)
      printf(RED "\t\t\t[STATUS: FAIL]\n" RESET);

    (*fails)++;
  }
}



void displayTestResults(int* fails) {
  printf("----END TEST----\n");
  printf(YELLOW "RESULTS: " RESET);
  if (*fails > 0)
    printf(RED "FAILURE. Total test fails: %d\n" RESET, *fails);
  else
    printf(GREEN "SUCCESS. All tests pass.\n" RESET);
  printf("----------------\n");
}

