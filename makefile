.DEFAULT_GOAL := compile

cc = gcc
CFLAGS = -Wall -pedantic -std="gnu99" -O3

compile: main.o src/linkedList.o src/readCohorts.o src/readClasses.o src/sortClasses.o src/findCombinations.o
	$(cc) $(CFLAGS) main.o src/linkedList.o src/readCohorts.o src/readClasses.o src/sortClasses.o src/findCombinations.o -o cohorts -lm

main.o: src/main.c src/linkedList.h src/readCohorts.h src/readClasses.h src/sortClasses.h src/findCombinations.h
	$(cc) $(CFLAGS) -c src/main.c -o main.o

linkedList.o: 
	$(cc) $(CFLAGS) -c src/linkedList.c -o src/linkedList.o

linkedListTest.o: tests/linkedListTest.c
	$(cc) $(CFLAGS) -c tests/linkedListTest.c -o tests/linkedListTest.o -lcunit

linkedListTest: tests/linkedListTest.o src/linkedList.o
	$(cc) $(CFLAGS) src/linkedList.o tests/linkedListTest.o -o tests/linkedListTest -lcunit
	./tests/linkedListTest

readClasses.o: src/linkedList.o
	$(cc) $(CFLAGS) -lm -c src/readClasses.c -o src/readClasses.o

readClassesTest.o: tests/readClassesTest.c
	$(cc) $(CFLAGS) -c tests/readClassesTest.c -o tests/readClassesTest.o -lcunit -lm

readClassesTest: tests/readClassesTest.o src/readClasses.o
	$(cc) $(CFLAGS) src/readClasses.o src/linkedList.o tests/readClassesTest.o -o tests/readClassesTest -lcunit -lm
	./tests/readClassesTest

readCohorts.o: src/linkedList.o
	$(cc) $(CFLAGS) -g -lm -c src/readCohorts.c -o src/readCohorts.o

readCohortsTest.o: tests/readCohortsTest.c
	$(cc) $(CFLAGS) -c tests/readCohortsTest.c -o tests/readCohortsTest.o -lcunit -lm

readCohortsTest: tests/readCohortsTest.o src/readCohorts.o
	$(cc) $(CFLAGS) src/readCohorts.o src/linkedList.o tests/readCohortsTest.o -o tests/readCohortsTest -lcunit -lm
	./tests/readCohortsTest

sortClasses.o: src/linkedList.o src/readCohorts.o src/readClasses.o
	$(cc) $(CFLAGS) -lm -c src/sortClasses.c -o src/sortClasses.o

sortClassesTest.o: tests/sortClassesTest.c
	$(cc) $(CFLAGS) -c tests/sortClassesTest.c -o tests/sortClassesTest.o -lcunit -lm

sortClassesTest: tests/sortClassesTest.o src/sortClasses.o
	$(cc) $(CFLAGS) src/sortClasses.o src/linkedList.o src/readClasses.o src/readCohorts.o tests/sortClassesTest.o -o tests/sortClassesTest -lcunit -lm
	./tests/sortClassesTest

findCombinations.o: src/linkedList.o src/readCohorts.o src/readClasses.o src/sortClasses.o
	$(cc) $(CFLAGS) -lm -c src/findCombinations.c -o src/findCombinations.o

clean:
	rm -f *.o cohorts *Test src/*.o output.txt
