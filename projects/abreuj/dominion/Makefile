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




# ========= UNIT TESTS WEEK 2 AND 3 ============
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


unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	echo -e 'Author: James Cameron Abreu' &> unittestresults.out
	echo -e 'Winter, 2018' >> unittestresults.out
	echo -e 'CS 362-400, week 03 & 04' >> unittestresults.out
	echo -e 'NOTE: in vim, hold "z" and press "M" for folding' >> unittestresults.out
	echo -e '      then, you can open a fold with "z" and "o"\n\n' >> unittestresults.out
	echo -e '\n\n\n' >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest1.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest2.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest3.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: cardtest4.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest1.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest1 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest2.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest3.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo -e '\n\n\n|------------------------------|' >> unittestresults.out
	echo -e       '|     FILE: unittest4.c        |' >> unittestresults.out
	echo -e       '|------------------------------|\n\n' >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo -e '\n\n\n' >> unittestresults.out
	echo -e '\n\n\n==========================' >> unittestresults.out
	echo    ' DOMINION COVERAGE ' >> unittestresults.out
	echo    '==========================' >> unittestresults.out
	echo -e '\n\n|------------------------------|' >> unittestresults.out
	echo -e   '|     FILE: dominion.c         |' >> unittestresults.out
	echo -e   '|------------------------------|\n\n' >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo -e       '\n\n****** END OF TEST FILES *******\n\n' >> unittestresults.out

# End my tests week 2 and 3 -------------------





# ========= UNIT TESTS WEEK 4 AND 5 ============
randomtestcard1: dominion.o randomtestcard1.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o randomtestcard1 randomtestcard1.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o randomtestcard2 randomtestcard2.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: dominion.o randomtestadventurer.c testUtilityFunctions.c testUtilityFunctions.h
	gcc -o randomtestadventurer randomtestadventurer.c testUtilityFunctions.c dominion.o rngs.o $(CFLAGS)


# ==== Run random test files through MANY tests ====
random_adventurer: randomtestadventurer
	./randomtestadventurer 1 > randomtestadventurer.results
	i=2 ; while [[ $$i -le 200 ]] ; do \
		./randomtestadventurer $$i >> randomtestadventurer.results ; \
		((i = i + 1)) ; \
	done

random_card1: randomtestcard1
	./randomtestcard1 1 > randomtestcard1.results
	i=2 ; while [[ $$i -le 200 ]] ; do \
		./randomtestcard1 $$i >> randomtestcard1.results ; \
		((i = i + 1)) ; \
	done

random_card2: randomtestcard2
	./randomtestcard2 1 > randomtestcard2.results
	i=2 ; while [[ $$i -le 200 ]] ; do \
		./randomtestcard2 $$i >> randomtestcard2.results ; \
		((i = i + 1)) ; \
	done


# Run all of my random tests and then output results and find coverage:
random_all: randomtestadventurer randomtestcard1 randomtestcard2
	echo -e 'Author: James Cameron Abreu' &> randomTests.results
	echo -e 'Winter, 2018' >> randomTests.results
	echo -e 'CS 362-400, week 03 & 04' >> randomTests.results
	echo -e 'NOTE: in vim, hold "z" and press "M" for folding' >> randomTests.results 
	echo -e '      then, you can open a fold with "z" and "o"\n\n' >> randomTests.results
	echo -e '\n\n\n' >> randomTests.results
	echo -e '\n\n\n|------------------------------|' >> randomTests.results
	echo -e       '| FILE: randomtestadventurer.c |' >> randomTests.results
	echo -e       '|------------------------------|\n\n' >> randomTests.results
	i=1 ; while [[ $$i -le 200 ]] ; do \
		./randomtestadventurer $$i >> randomTests.results ; \
		((i = i + 1)) ; \
	done
	echo -e '\n\n\n|------------------------------|' >> randomTests.results
	echo -e       '| FILE: randomtestcard1.c      |' >> randomTests.results
	echo -e       '|------------------------------|\n\n' >> randomTests.results
	i=1 ; while [[ $$i -le 200 ]] ; do \
		./randomtestcard1 $$i >> randomTests.results ; \
		((i = i + 1)) ; \
	done
	echo -e '\n\n\n|------------------------------|' >> randomTests.results
	echo -e       '| FILE: randomtestcard2.c      |' >> randomTests.results
	echo -e       '|------------------------------|\n\n' >> randomTests.results
	i=1 ; while [[ $$i -le 200 ]] ; do \
		./randomtestcard2 $$i >> randomTests.results ; \
		((i = i + 1)) ; \
	done
	echo -e '\n\n\n' >> randomTests.results
	echo -e '\n\n\n==========================' >> randomTests.results
	echo    ' DOMINION COVERAGE ' >> randomTests.results
	echo    '==========================' >> randomTests.results
	echo -e '\n\n|------------------------------|' >> randomTests.results
	echo -e   '|     FILE: dominion.c         |' >> randomTests.results
	echo -e   '|------------------------------|\n\n' >> randomTests.results
	gcov dominion.c >> randomTests.results
	cat dominion.c.gcov >> randomTests.results
	echo -e       '\n\n****** END OF TEST FILES *******\n\n' >> randomTests.results

# End my tests week 4 and 5 -------------------





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
	rm -rf *.results
