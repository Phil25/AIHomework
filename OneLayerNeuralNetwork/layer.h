#include <vector>
#include <array>

#include "perc.h"

#ifndef LAYER_H
#define LAYER_H


class layer{
	std::vector<perc> percs;
	const int network_size;
	const int input_size;

public:
	layer(int network_size, const int input_size, const double learning_param);
	int get(double* letters);
	double train(double* letters, int correct_output);

	friend std::ostream& operator<<(std::ostream&, const layer&);

};


#endif
