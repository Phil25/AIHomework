#include <iostream>
#include <vector>

#ifndef PERC_H
#define PERC_H

class perc{
	const unsigned int num_of_coords;
	std::vector<double> weights;
	double threshold;
	double learning_param;

public:
	perc(const unsigned int num_of_coords, const double learning_param);

	double get(const double* inputs);
	void tune(const double* inputs, double actual, double correct);

	friend std::ostream& operator<<(std::ostream&, const perc&);

};

#endif
