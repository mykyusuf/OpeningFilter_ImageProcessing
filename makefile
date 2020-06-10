all: myk

myk: main.o
	g++ -std=c++11 main.o -o myk
	./myk

main.o: main.cpp
	g++ -c main.cpp


clean:
	rm *.o myk

