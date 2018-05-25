#include <fstream>
#include <sstream>

#include "char_vector.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[0;36m"

#define COLOR_PROP COLOR_GREEN
#define COLOR_VAL COLOR_CYAN

namespace dr{

	// hidden readers
	namespace{
		int read(std::istringstream& iss){
			std::string data;
			iss >> data;
			return std::stoi(data);
		}

		// parse line in a data set
		item parse_line(std::string& line){
			std::istringstream iss(line);
			return item{read(iss), read(iss)};
		}
	}

	// read a data file to a provided vector vec
	int read_data(std::string file, std::vector<item>& vec){
		std::ifstream fs(file);
		std::string data;

		std::getline(fs, data);
		int cap = std::stoi(data);

		int limit = 0;
		while(std::getline(fs, data)){
			vec.push_back(parse_line(data));
			if(++limit > 6)
				break;
		}
		return cap;
	}

}
