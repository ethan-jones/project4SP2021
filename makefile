TreeDr: TreeDr.o
	g++ -o TreeDr TreeDr.o

TreeDr.o: TreeDr.cpp TreeType.o
	g++ -o TreeDr.o -c TreeDr.cpp TreeType.o

TreeType.o: TreeType.cpp QueType.o TreeType.h
	g++ -o TreeType.o -c TreeType.cpp QueType.o TreeType.h

QueType.o: QueType.cpp QueType.h
	g++ -o QueType.o -c QueType.cpp QueType.h
