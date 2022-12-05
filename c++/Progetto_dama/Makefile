playerh: player.o main.o
	g++ -std=c++14 player.o main.o -oplayerh


player.o: player.cpp player.hpp
	g++ -std=c++14 -c player.cpp -oplayer.o

main.o: main.cpp player.hpp
	g++ -std=c++14 -c main.cpp -omain.o

clean:
	rm playerh player.o main.o