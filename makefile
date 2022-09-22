nqueens: queen.o stack.o board.o main.o
	g++ -g queen.o board.o main.o -o nqueens

main.o: main.cpp
	g++ -c -g main.cpp

queen.o: queen.h queen.cpp
	g++ -c -g queen.cpp

board.o: board.h board.cpp
	g++ -c -g board.cpp

stack.o: stack.h
	g++ -c -g stack.h

clean:
	rm *.o
	rm nqueens

run: nqueens
	./nqueens

debug: nqueens
	gdb nqueens
