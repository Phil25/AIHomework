#include <iostream>

#ifndef FRACTION_H
#define FRACTION_H


struct fraction{
	double nominator = 0, denominator = 1;

	inline void smooth(double nominator, double denominator){
		this->nominator += nominator;
		this->denominator += denominator;
	}

	inline double result(){
		return nominator /denominator;
	}

	void operator*=(const fraction& other){
		this->nominator *= other.nominator;
		this->denominator *= other.denominator;
	}

	friend std::ostream& operator<<(std::ostream&, const fraction&);

};

std::ostream& operator<<(std::ostream& os, const fraction& frac){
	return os << (frac.nominator /frac.denominator);
}

#endif
