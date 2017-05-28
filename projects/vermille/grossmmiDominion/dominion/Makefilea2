CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

randomtestcard1: randomtestcard1.c dominion.h dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.h dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.h dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

assign4:
	make clean
	make randomtestcard1
	make randomtestcard2
	make randomtestadventurer
	rm -f randomtestcard1.out
	rm -f randomtestcard2.out
	rm -f randomtestadventurer.out
	./randomtestcard1 >> randomtestcard1.out
	./randomtestcard2 >> randomtestcard2.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard2.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gov >> randomtestcard1.out
	cat dominion.c.gov >> randomtestcard2.out
	cat dominion.c.gov >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestreslts.out: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	echo "Result for running BST tests:" > tests.out

	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 dominion.o rngs.o unittest1.c $(CFLAGS)
	unittest1 >> unittestreslts.out
	gcov bst.o >> unittestreslts.out

	echo "unittest2.c:" >> tests.out
	gcc -o unittest2 dominion.o rngs.o unittest2.c $(CFLAGS)
	unittest2 >> unittestreslts.out
	gcov bst.o >> unittestreslts.out

	echo "unittest3.c:" >> tests.out
	gcc -o unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)
	unittest3 >> unittestreslts.out
	gcov bst.o >> unittestreslts.out

	echo "unittest4.c:" >> tests.out
	gcc -o unittest4 dominion.o rngs.o unittest4.c $(CFLAGS)
	unittest4 >> unittestreslts.out
	gcov bst.o >> unittestreslts.out


all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittestreslts.out *.gcov *.gcda *.gcno *.so
