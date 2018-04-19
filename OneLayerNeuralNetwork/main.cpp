#include <iostream>

#include "data_reader.h"
#include "layer.h"

#define TEST

std::vector<lang_data> data;

int main(){

	// read data
	std::string dir_name = "./training";
	if(!dr::get_lang_data(dir_name.c_str(), data)){
		std::cout << "Cannot open directory" << std::endl;
		return 1;
	}

	// number of languages detected
	const int lang_count = data.size();
	std::cout << lang_count << " languages detected." << std::endl;
	std::cout << dr::to_string(data) << std::endl;

	// user input of the learning parameter
	double learning_param = 0.1;
#ifndef TEST
	std::cout << "Learning parameter: ";
	std::cin >> learning_param;
#endif

	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;
	std::cout << "==========" << std::endl;

	std::cout << "Input size: " << LETTER_COUNT << std::endl;
	layer l = layer(lang_count, LETTER_COUNT, learning_param);
	while(1){
		double error = 0.0;

		// iterate every language and every document
		for(int i = 0; i < lang_count; i++){
			for(int j = 0; j < DOCUMENT_COUNT; j++)
				error += l.train(data[i].freq[j].begin(), i);
			std::cout << "==========" << std::endl;
		}

		//std::cout << "Error: " << error << std::endl;
		if(error < 50)
			break;
	}
	std::cout << l << std::endl;

	int test_lang = 3;
	std::cout << data[test_lang].lang << std::endl;
	int result = l.get(data[test_lang].freq[4].begin());
	std::cout << data[result].lang << std::endl;

	return 0;
}
