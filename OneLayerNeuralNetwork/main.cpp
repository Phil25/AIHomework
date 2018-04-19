#include <iostream>

#include "data_reader.h"
#include "layer.h"

//#define TEST

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

	// user input of the learning parameter
	double learning_param = 0.1;
#ifndef TEST
	std::cout << "Learning parameter: ";
	std::cin >> learning_param;
#endif

	//std::cout << "Input size: " << LETTER_COUNT << std::endl;
	layer l = layer(lang_count, LETTER_COUNT, learning_param);
	double error = 0.0;
	while(1){
		error = 0.0;

		// iterate every language and every document
		for(int i = 0; i < lang_count; i++)
			for(int j = 0; j < DOCUMENT_COUNT; j++)
				error += l.train(data[i].freq[j].begin(), i);

		// break on acceptable error
		if(error < 15.1)
			break;
	}
	std::cout << "Accepted training with " << error << " error." << std::endl;

	// test the nn
	double accuracy = 0.0;
	for(int i = 0; i < lang_count; i++)
		for(int j = 0; j < DOCUMENT_COUNT; j++){

			std::cout << "Actual: " << data[i].lang << ", guess: ";

			int result = l.get(data[i].freq[j].begin());
			std::cout << data[result].lang;

			if(i != result)
				std::cout << " <";
			else accuracy++;

			std::cout << std::endl;
		}
	std::cout << "Accuracy: " << (accuracy/(lang_count *DOCUMENT_COUNT)*100) << '%' << std::endl;

	return 0;
}
