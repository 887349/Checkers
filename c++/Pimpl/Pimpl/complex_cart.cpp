#include<iostream>
#include"comp.hpp"

class Impl{
	public:
		double x;
		double y;
};

Complex::Complex() {
	pimpl = new Impl;
	pimpl->x = 0.0;
	pimpl->y = 0.0;
}

Complex::Complex(double real) {
	pimpl = new Impl;
	pimpl->x = real;
	pimpl->y = 0.0;
}


Complex::Complex(double real, double imag) {
	pimpl = new Impl;
	pimpl->x = real;
	pimpl->y = imag;
}

Complex::Complex(const Complex& c) {
	pimpl = new Impl;
	pimpl->x = c.pimpl->x;
	pimpl->y = c.pimpl->y;
}

Complex::~Complex() {
	delete pimpl;
}

bool Complex::operator==(const Complex& c) const{
	return ((pimpl->x == c.pimpl->x) && (pimpl->y == c.pimpl->y));
}

Complex Complex::operator+(const Complex& c) const {
	Complex res;
	res.pimpl->x = pimpl->x+c.pimpl->x;
	res.pimpl->y = pimpl->y+c.pimpl->y;
	return res;
}

Complex Complex::operator*(const Complex& c) const{
	Complex z;
	z.pimpl->x = pimpl->x*c.pimpl->x - pimpl->y*c.pimpl->y;
	z.pimpl->y = pimpl->x*c.pimpl->y + pimpl->y*c.pimpl->x;
	return z;
}

Complex& Complex::operator=(const Complex& c){
	pimpl->x = c.pimpl->x;
	pimpl->y = c.pimpl->y;
	return *this;
}

void Complex::print() const{
	std::cout<<"("<<pimpl->x<<" + i"<<pimpl->y<<")";
}



