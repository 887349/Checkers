comp: complex_cart.o main.o
	g++ -std=c++14 complex_cart.o main.o -ocomp


complex_cart.o: complex_cart.cpp comp.hpp
	g++ -std=c++14 -c complex_cart.cpp -ocomplex_cart.o

main.o: main.cpp comp.hpp
	g++ -std=c++14 -c main.cpp -omain.o

clean:
	rm comp complex_cart.o main.o


