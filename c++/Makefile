comp: player.o main.o
	g++ -std=c++14 player.o main.o -oplay


complex_cart.o: player.cpp player.hpp
	g++ -std=c++14 -c player.cpp -oplay.o

main.o: main.cpp player.hpp
	g++ -std=c++14 -c main.cpp -omain.o

clean:
	rm comp player.o main.o