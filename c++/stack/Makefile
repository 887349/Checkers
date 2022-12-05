teststack: main.o stack_list.o
	g++ -std=c++14 stack_list.o main.o -oteststack

main.o: main.cpp stack.hpp
	g++ -c -std=c++14 main.cpp -omain.o

stack_vect.o: stack_vect.cpp stack.hpp
	g++ -c -std=c++14 stack_vect.cpp -ostack_vect.o

stack_list.o: stack_list.cpp stack.hpp
	g++ -c -std=c++14 stack_list.cpp -ostack_list.o

clean:
	rm *.o teststack


