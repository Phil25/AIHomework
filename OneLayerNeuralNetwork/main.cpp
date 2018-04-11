#include <iostream>

#include "perc.h"
#include "data_reader.h"

std::vector<perc> percs;
std::vector<lang_data> data;

int main(){

	std::string dir_name = "./training";
	if(!dr::get_lang_data(dir_name.c_str(), data)){
		std::cout << "Cannot open directory" << std::endl;
		return 1;
	}

	std::cout << data.size() << " languages detected." << std::endl;
	std::cout << dr::to_string(data) << std::endl;

	return 0;
}
