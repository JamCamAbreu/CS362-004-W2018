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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out




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

# End my tests week 4 and 5 -------------------




# Test coverage of my unit tests:
getCoverage: cardtest1 cardtest2 cardtest3 unittest1 unittest2 unittest3 unittest4 randomtestadventurer randomtestcard1 
	echo -e 'Author: James Cameron Abreu\n' &> cardtest1.out
	echo -e 'Coverage Results\n' >> cardtest1.out
	echo -e '------------------------\n\n\n' >> cardtest1.out
	./cardtest1 >> cardtest1.out
	gcov dominion.c -b >> cardtest1.out
	cat dominion.c.gcov >> cardtest1.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> cardtest2.out
	echo -e 'Coverage Results\n' >> cardtest2.out
	echo -e '------------------------\n\n\n' >> cardtest2.out
	./cardtest2 >> cardtest2.out
	gcov dominion.c -b >> cardtest2.out
	cat dominion.c.gcov >> cardtest2.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> cardtest3.out
	echo -e 'Coverage Results\n' >> cardtest3.out
	echo -e '------------------------\n\n\n' >> cardtest3.out
	./cardtest3 >> cardtest3.out
	gcov dominion.c -b >> cardtest3.out
	cat dominion.c.gcov >> cardtest3.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> unittest1.out
	echo -e 'Coverage Results\n' >> unittest1.out
	echo -e '------------------------\n\n\n' >> unittest1.out
	./unittest1 >> unittest1.out
	gcov dominion.c -b >> unittest1.out
	cat dominion.c.gcov >> unittest1.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> unittest2.out
	echo -e 'Coverage Results\n' >> unittest2.out
	echo -e '------------------------\n\n\n' >> unittest2.out
	./unittest2 >> unittest2.out
	gcov dominion.c -b >> unittest2.out
	cat dominion.c.gcov >> unittest2.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> unittest3.out
	echo -e 'Coverage Results\n' >> unittest3.out
	echo -e '------------------------\n\n\n' >> unittest3.out
	./unittest3 >> unittest3.out
	gcov dominion.c -b >> unittest3.out
	cat dominion.c.gcov >> unittest3.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> unittest4.out
	echo -e 'Coverage Results\n' >> unittest4.out
	echo -e '------------------------\n\n\n' >> unittest4.out
	./unittest4 >> unittest4.out
	gcov dominion.c -b >> unittest4.out
	cat dominion.c.gcov >> unittest4.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> randomtestadventurer.out
	echo -e 'Coverage Results\n' >> randomtestadventurer.out
	echo -e '------------------------\n\n\n' >> randomtestadventurer.out
	i=1 ; while [[ $$i -le 200 ]] ; do \
		./randomtestadventurer $$i >> randomtestadventurer.out ; \
		((i = i + 1)) ; \
	done
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	rm dominion.c.gcov		# clear gcov for next coverage test
	echo -e 'Author: James Cameron Abreu\n' &> randomtestcard1.out
	echo -e 'Coverage Results\n' >> randomtestcard1.out
	echo -e '------------------------\n\n\n' >> randomtestcard1.out
	i=1 ; while [[ $$i -le 200 ]] ; do \
		./randomtestcard1 $$i >> randomtestcard1.out ; \
		((i = i + 1)) ; \
	done







player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -rf *.results
