g++Flags = -std="c++17" -Wall -Werror

build: afterTime.cpp afterTime.hpp
	g++ $(g++Flags) -c afterTime.cpp -o afterTime.o

test: afterTime.o test.o
	g++ $(g++Flags) afterTime.o test.o -o test

runTests: test
	./test

test.o: afterTime.hpp afterTimeTest.cpp
	g++ $(g++Flags) -c afterTimeTest.cpp -o test.o