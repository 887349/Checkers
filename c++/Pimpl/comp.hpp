#ifndef COMPLEX
#define COMPLEX

class Impl;

class Complex{
	public:
		Complex();
		Complex(double real);
		Complex(double real, double imag);
		Complex(const Complex& c);

		~Complex();

		bool operator==(const Complex& c) const;
		Complex operator+(const Complex& c) const;
		Complex operator*(const Complex& c) const;
		Complex& operator=(const Complex& c);

		void print() const;

	private:
		Impl* pimpl;
};

#endif

