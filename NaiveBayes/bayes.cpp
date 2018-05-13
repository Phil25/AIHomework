#include <iostream>

#include "data_reader.h"

// vectors storing train and test data
std::vector<car> data;

int main(){

	// parse assignment files
	dr::read_data("training", data);

	for(auto it = data.begin(); it != data.end(); it++)
		std::cout << *it << std::endl;

	return 0;
}
