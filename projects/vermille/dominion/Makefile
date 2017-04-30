CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

adventurer:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurer.c rngs.c -o randomtestadventurer -lm -g

adventurerBetter:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestadventurerBetter.c rngs.c -o randomtestadventurerBetter -lm -g

runAdventurer: adventurer
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

runAdventurerBetter: adventurerBetter
	./randomtestadventurerBetter &> randomtestadventurerBetter.out
	gcov dominion.c >> randomtestadventurerBetter.out
	cat dominion.c.gcov >> randomtestadventurerBetter.out

randomcard:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard.c rngs.c -o randomtestcard -lm -g

randomcardBetter:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcardBetter.c rngs.c -o randomtestcardBetter -lm -g

runRandomCard: randomcard
	./randomtestcard &> randomtestcard.out
	gcov dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out

runRandomCardBetter: randomcardBetter
	./randomtestcardBetter &> randomtestcardBetter.out
	gcov dominion.c >> randomtestcardBetter.out
	cat dominion.c.gcov >> randomtestcardBetter.out


playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

playdom2: dominion.o playdom2.c
	gcc -o playdom2 playdom2.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Result for running unit tests:" >  unittestresults.out	
	echo "unittest1.c:" >>  unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "unittest2.c:" >>  unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c $(CFLAGS)
	unittest2 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "unittest3.c:" >>  unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c $(CFLAGS)
	unittest3 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "unittest4.c:" >>  unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "cardtest1.c:" >>  unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "cardtest2.c:" >>  unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "cardtest3.c:" >>  unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)
	cardtest3 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

	echo "cardtest4.c:" >>  unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)
	cardtest4 >>  unittestresults.out
	gcov -b dominion.c >>  unittestresults.out

testDominion:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c testdominion.c rngs.c -o testdominion -lm -g

testdom: testDominion
	./testdominion &> gameResults.out
	gcov dominion.c >> gameResults.out
	cat dominion.c.gcov >> gameResults.out

testdom2: testDominion
	./testdominion &> gameResults2.out
	gcov dominion.c >> gameResults2.out
	cat dominion.c.gcov >> gameResults2.out

completeTestSet: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 testDominion
	./unittest1 &> ctsResults.out
	./unittest2 >> ctsResults.out
	./unittest3 >> ctsResults.out
	./unittest4 >> ctsResults.out
	./cardtest1 >> ctsResults.out
	./cardtest2 >> ctsResults.out
	./cardtest3 >> ctsResults.out
	./cardtest4 >> ctsResults.out
	gcov dominion.c >> ctsResults.out
	./testdominion >> ctsResults.out
	gcov dominion.c >> ctsResults.out


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
	rm -f *.o playdom.exe playdom test.exe test dominion testDrawCard badTestDraw player interface rngs unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

