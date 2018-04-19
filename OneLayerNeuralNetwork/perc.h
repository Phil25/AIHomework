#include <iostream>

#ifndef PERC_H
#define PERC_H

class perc{
public:
	perc(const unsigned int num_of_coords, const double learning_param);
	~perc();

	double get(const double* inputs);
	void tune(const double* inputs, double actual, double correct);

	friend std::ostream& operator<<(std::ostream&, const perc&);

private:
	const unsigned int num_of_coords;
	double* weights;
	double threshold;
	double learning_param;

};

#endif
