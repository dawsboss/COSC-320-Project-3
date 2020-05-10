output: main.o
	g++ -std=c++11 main.o -o main -g

main.o: Graph.h Graph.cpp main.cpp
	g++ -c -g -std=c++11 main.cpp

clean:
	rm *.o -f main

submit:
	make clean; zip Project3.zip *
