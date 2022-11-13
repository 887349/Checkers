#include "comp.hpp"

int main() {
	Complex x;
	Complex y(34);
	Complex z(0,1);
	Complex w(2, 5);

	Complex k;

	k=y*z*w+x;

	k.print();

	return 0;
}
