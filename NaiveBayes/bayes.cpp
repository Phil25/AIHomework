#include <iostream>

#include "data_reader.h"

std::string bayes(const car& c, std::vector<car>& data){
	return "";
}

void run_test(std::vector<car>& test_data, std::vector<car>& training_data){
	float all = 0, correct = 0;

	auto end = test_data.end();
	for(auto it = test_data.begin(); it != end; it++){
		std::string guess = bayes(*it, training_data);
		correct += guess.compare(it->acceptability) == 1;
		all++;
	}

	std::cout << "Accuracy: " << all /correct *100 << "%" << std::endl;
}

int main(){

	// vectors storing train and test data
	std::vector<car> test_data;
	std::vector<car> training_data;

	// parse assignment files
	dr::read_data("test", test_data);
	dr::read_data("training", training_data);
	dr::calc_unique_values(training_data);

	// run the algorithm for the test data
	run_test(test_data, training_data);

	return 0;
}
