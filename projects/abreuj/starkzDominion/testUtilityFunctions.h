/*************************************
 * Author: James Cameron Abreu
 * Date: 01/30/2018
 * ------------------------------
 * My own functions to help with unit testing
 * for the dominion c code. 
 * CS 362-400, Winter 2018
 ************************************/

#ifndef TEST_UTIL_FUNCTIONS
#define TEST_UTIL_FUNCTIONS

#include <stdio.h>

// CHANGE THIS '#if 0' to '#if 1' to turn on colors

#if 0
  #define RED     "\x1b[31m"
  #define YELLOW  "\x1b[33m"
  #define GREEN   "\x1b[32m"
  #define RESET   "\033[0m"
#else
  #define RED     ""
  #define YELLOW  ""
  #define GREEN   ""
  #define RESET   ""
#endif




// Prints out to the terminal indicated whether a condition passed or failed. 
// The fails variable should start with 0. If there was an error, it
// will be incremented, thus overall (with several of these function calls),
// the variable will grow with any errors in the program. 
void testCondition(int condition, int* fails, int display);


void displayTestResults(int* fails);

#endif
