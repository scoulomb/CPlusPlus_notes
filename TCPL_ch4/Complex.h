									/*
 * Complex.h
 *
 *  Created on: Feb 20, 2016
 *      Author: scoulomb
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

#include<ostream>

namespace tcpl {

class Complex {

private:
	double _re, _im;


public:
	Complex(double, double);
	Complex(double);
	Complex();

	double real() const;
	void real(double d);
	double imag() const;
	void imag(double d);

	Complex& operator+(Complex);
	Complex& operator-(Complex);

	Complex& operator*=(Complex);
	Complex& operator/=(Complex);


	//virtual ~Complex();
};

Complex operator+(Complex, Complex);
Complex operator-(Complex, Complex);
Complex operator-(Complex);
Complex operator*(Complex, Complex);
Complex operator/(Complex, Complex);

bool operator==(Complex, Complex);
bool operator!=(Complex, Complex);

//std::ostream& operator<<(std::ostream& os, Complex)
//{
//	os << "YOLO";
//	return os;
//}

}

#endif /* COMPLEX_H_ */
