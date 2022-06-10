#Makefile M00738240 Software Enginering Coursework 2
all: librarySystem test

librarySystem: dependencies.h main.o Book.o RedBlackTree.o DataLoader.o Gui.o
	g++ -std=c++17 RedBlackTree.o Book.o DataLoader.o Gui.o main.o -o librarySystem

Book.o: Book.cpp
	g++ -std=c++17 -c Book.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

RedBlackTree.o: RedBlackTree.cpp
	g++ -std=c++17 -c RedBlackTree.cpp

DataLoader.o: DataLoader.cpp
	g++ -std=c++17 -c DataLoader.cpp

Gui.o: Gui.cpp
	g++ -std=c++17 -c Gui.cpp

test: AutomatedTests.cpp dependencies.h catch.hpp
	g++ -std=c++17 AutomatedTests.cpp -o test

clean:
	rm *.o librarySystem test