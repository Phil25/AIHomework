#include <iostream>

#ifndef FRACTION_H
#define FRACTION_H


struct fraction{
	double nominator = 0, denominator = 1;
	double snom = 0, sden = 0;

	inline void smooth(double nominator, double denominator){
		this->nominator += nominator;
		this->denominator += denominator;
		snom = nominator;
		sden = denominator;
	}

	inline double result() const{
		return nominator /denominator;
	}

	void operator*=(const fraction& other){
		this->nominator *= other.nominator;
		this->denominator *= other.denominator;
	}

	friend bool operator<=(const fraction&, const fraction&);
	friend std::ostream& operator<<(std::ostream&, const fraction&);

};

std::ostream& operator<<(std::ostream& os, const fraction& frac){
	os << (frac.nominator -frac.snom) << '+' << frac.snom;
	os << '/';
	os << (frac.denominator -frac.sden) << '+' << frac.sden;
	os << " = ";
	os << frac.nominator << '/' << frac.denominator;
	os << " = ";
	os << frac.result();
	return os;
}

bool operator<=(const fraction& a, const fraction& b){
	return a.result() <= b.result();
}

#endif
