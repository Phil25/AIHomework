#include <random>
#include <ctime>
#include "perc.h"

double seed = std::time(0);

double small_rand(double max){
	std::srand(seed);
	double result = (double)std::rand() /RAND_MAX *max;
	seed *= result;
	return result;
}

perc::perc(const unsigned int num_of_coords, const double learning_param):
	num_of_coords(num_of_coords),
	weights(new double[num_of_coords]),
	threshold(small_rand(5)),
	learning_param(learning_param)
{
	for(unsigned int i = 0; i < num_of_coords; i++)
		weights[i] = small_rand(5);
}

perc::~perc(){
	delete [] weights;
}

double perc::get_threshold(){
	return threshold;
}

// perceptron decision method
bool perc::get(const double* inputs){
	// SUM(x[i] *w[i]) >= threshold
	double sum = 0.0;
	for(unsigned int i = 0; i < num_of_coords; i++)
		sum += weights[i] *inputs[i];
	return sum >= threshold;
}

// perception learning rule application
void perc::tune(const double* inputs, bool actual, bool correct){
	// W = W + (y-d) a X
	for(unsigned int i = 0; i < num_of_coords; i++)
		weights[i] += (actual -correct) *learning_param *inputs[i];
	// O = O - (d-y) a
	threshold -= (correct-actual) *learning_param;
}

std::ostream& operator<<(std::ostream& os, const perc& p){
	os << "Threshold = " << p.threshold << ",\nWeights[" << p.num_of_coords << "] = {\n";
	for(unsigned int i = 0; i < p.num_of_coords; i++)
		os << '\t' << p.weights[i] << '\n';
	os << '}';
	return os;
}
