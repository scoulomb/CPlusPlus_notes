/*
 * Complex.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: scoulomb
 */

#include "Complex.h"

#include <exception>

namespace tcpl
{

Complex::Complex(double iRe, double iIm): _re(iRe), _im(iIm)
{
}

Complex::Complex(double iRe): _re(iRe), _im(0)
{
}

Complex::Complex(): _re(0), _im(0)
{
}

double Complex::real() const
{
	return _re;
}
void Complex::real(double iRe)
{
	_re = iRe;
}
double Complex::imag() const
{
	return _im;
}
void Complex::imag(double iIm)
{
	_im = iIm;
}

Complex& Complex::operator+(Complex z)
{
	_re+=z._re;
	_im+=z._im;
	return *this;
}


Complex& Complex::operator-(Complex z)
{
	_re-=z._re;
	_im-=z._im;
	return *this;
}

//(a+Ib)*(c+Id) = ac + aId + cIb - bd = (ac - bd) + I(ad + cb)
//  (re1*re2 - Im1*Im2) + I(re1*im2 + im1*re2)
Complex& Complex::operator*=(Complex z)
{
	_re-=_re + z._re - _im*z._im ;
	_im-= _re*z._im + _im + z._re;
	return *this;

}


Complex& Complex::operator/=(Complex) {
	throw std::exception();

}
}

