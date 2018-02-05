CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)


# Here is my tests -----------------------------
# CARD TESTS
cardtest1: dominion.o cardtest1.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o cardtest1 cardtest1.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o cardtest2.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o cardtest2 cardtest2.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o cardtest3.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o cardtest3 cardtest3.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o cardtest4.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o cardtest4 cardtest4.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)


# UNIT TESTS
unittest1: dominion.o unittest1.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o unittest1 unittest1.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o unittest2 unittest2.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o unittest3.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o unittest3 unittest3.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o unittest4.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o unittest4 unittest4.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

# End my tests week 2 and 3 -------------------


unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	echo -e 'Author: James Cameron Abreu' &> unittestresults.out
	echo -e 'Winter, 2018' >> unittestresults.out
	echo -e 'CS 362-400, week 03 & 04' >> unittestresults.out
	echo -e 'NOTE: in vim, hold "z" and press "M" for easier viewing' >> unittestresults.out
	echo -e '      then, you can open a fold with "z" and "o"\n\n' >> unittestresults.out
	echo -e '\n\n\n'
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: dominion.c         |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest1.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest2.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest3.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest4.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest1.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest2.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest3.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest4.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	echo -e       '\n\n****** END OF TEST FILES *******\n\n' >> unittestresults.out






interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
