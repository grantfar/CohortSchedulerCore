cc = gcc
CFLAGS = -Wall -pedantic -std="gnu99" -g

build: rankFunctions.o afterTime.o stackRank.o timeBetweenClasses.o rank.o

rank.o: rank.c rank.h
	$(cc) $(CFLAGS) -c -o rank.o rank.c

rankFunctions.o: rankFunctions.c rankFunctions.h
	$(cc) $(CFLAGS) -c -o rankFunctions.o rankFunctions.c

afterTime.o: afterTime/afterTime.c afterTime/afterTime.h
	make -C afterTime

stackRank.o: moreClassesInDay/stackRank.c moreClassesInDay/stackRank.h
	make -C moreClassesInDay

timeBetweenClasses.o: timeBetweenClasses/timeBetweenClasses.h timeBetweenClasses/timeBetweenClasses.c
	make -C timeBetweenClasses

clean:
	rm -f rank.o rankFunctions.o moreClassesInDay/stackRank.o 