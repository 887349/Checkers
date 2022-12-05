#include"stack.hpp"
#include<iostream>


int main() {
	Stack_int s;

	for (int i=0; i<10; i++) {
	  int a;
	  std::cin>>a;
	  s.push(a);
	}

	while (!s.is_empty()) {
	  std::cout<<s.pop()<<std::endl;
	}


	return 0;
}
