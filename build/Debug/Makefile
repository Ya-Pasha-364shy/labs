all: lab1

lab1: main.o
	g++ main.o -o lab1

main.o: main.cpp
	g++ -Wall -Wextra -Wpedantic -c main.cpp

clean:
	rm -rf *.o lab1
