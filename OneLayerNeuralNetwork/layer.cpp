#include "layer.h"

layer::layer(int network_size, const int input_size, const double learning_param):
	network_size(network_size),
	input_size(input_size)
{
	while(network_size-- > 0)
		percs.push_back(perc(input_size, learning_param));
}

int layer::get(double* letters){
	int biggest_index = 0;
	double biggest_value = 0.0;

	// iterate through all perceptrons
	for(int i = 0; i < network_size; i++){

		// get the result for each
		double value = percs[i].get(letters);
		if(value <= biggest_value)
			continue;

		// save the biggest index
		biggest_index = i;
		biggest_value = value;
	}
	return biggest_index;
}

// correct_output indicates index of perceptron which should activate
// retuns the error delta
double layer::train(double* letters, int correct_output){
	// calculate error delta of this training
	double error_delta = 0.0;

	std::cout << "INPUT: correct: " << correct_output << ", {" << std::endl;
	for(int i = 0; i < 3; i++)
		std::cout << '\t' << letters[i] << std::endl;
	std::cout << '}' << std::endl;

	// iterate all perceptrons
	for(int i = 0; i < network_size; i++){
		double correct = (double)(i == correct_output);

		// tune result of each
		double result = percs[i].get(letters);
		std::cout << i << ". RESULT: " << result << std::endl;
		std::cout << i << ". PRE-TUNE: " << percs[i] << std::endl;
		percs[i].tune(letters, correct, result);
		std::cout << i << ". POST-TUNE: " << percs[i] << std::endl;

		// sum up the error delta
		double this_error = correct -result;
		error_delta += this_error *this_error;
	}
	std::cout << "==========" << std::endl;
	return error_delta/2;
}

std::ostream& operator<<(std::ostream& os, const layer& l){
	for(int i = 0; i < l.network_size; i++)
		os << l.percs[i] << std::endl;
	return os;
}
