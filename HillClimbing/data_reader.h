#include <fstream>
#include <sstream>
#include <iostream>

#include "graph.h"

namespace dr{

	namespace{
		void parse_line(std::string& line, graph& g){
			std::istringstream iss(line);
			for(int val; iss >> val;)
				g.add_col(val);
			g.add_row();
		}
	}

	// read a data file to a provided vector vec
	void read_data(std::string file, graph& g){
		std::ifstream fs(file);
		std::string data;

		while(std::getline(fs, data))
			parse_line(data, g);
	}

}
