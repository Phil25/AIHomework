#include <random>
#include <ctime>
#include <math.h>

#include "perc.h"

double seed = std::time(0);

double small_rand(double max){
	std::srand(seed);
	double result = (double)std::rand() /RAND_MAX *max;
	seed *= result;
	return 1;
}

double get_vector_length(std::vector<double> v, int size){
	double sumsq = 0.0;
	for(int i = 0; i < size; i++)
		sumsq += v[i] *v[i];
	return std::sqrt(sumsq);
}

void normalize_vector(std::vector<double> v, int size){
	double len = get_vector_length(v, size);
	for(int i = 0; i < size; i++)
		v[i] /= len;
}

perc::perc(const unsigned int num_of_coords, const double learning_param):
	num_of_coords(num_of_coords),
	threshold(small_rand(5)),
	learning_param(learning_param)
{
	// initialize the weights vector
	weights = std::vector<double>(num_of_coords);
	for(unsigned int i = 0; i < num_of_coords; i++)
		weights[i] = small_rand(5);

	// initial weights normalization
	normalize_vector(weights, num_of_coords);
}

// perceptron decision method
double perc::get(const double* inputs){
	// net = SUM(x[i] *w[i])
	double net = 0.0;
	for(unsigned int i = 0; i < num_of_coords; i++)
		net += weights[i] *inputs[i];

	// return sigmoid of net
	return 1/(1 +std::exp(-net));
}

// TODO: ask about net, whether the threshold is involved
// perception learning rule application
void perc::tune(const double* inputs, double correct, double actual){
	// W = W + n (d - y)y(1 - y)X
	double delta = learning_param *(correct -actual) *actual *(1 -actual);
	for(unsigned int i = 0; i < num_of_coords; i++)
		weights[i] += delta *inputs[i];

	// normalize weighs
	normalize_vector(weights, num_of_coords);
}

std::ostream& operator<<(std::ostream& os, const perc& p){
	os << "Threshold = " << p.threshold << ",\nWeights[" << p.num_of_coords << "] = {\n";
	for(unsigned int i = 0; i < p.num_of_coords; i++)
		os << '\t' << p.weights[i] << '\n';
	os << '}';
	return os;
}
