#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

// number of coordinates in the data set
#define COORD_NUM 4

// struct for holding the point;
struct point{
	std::string iris;
	std::array<double, COORD_NUM> coords;
	int owner; // cluster id this point belongs to
};

namespace dr{
	// parse line in a data set
	point parse_line(std::string& line){
		point p;
		std::istringstream iss(line);
		std::string data;

		// read coordinates
		int i = 0;
		while(std::getline(iss, data, ',') && i < COORD_NUM)
			p.coords[i++] = stod(data);

		// read class
		std::getline(iss, data);
		p.iris = data;

		return p;
	}

	// read a data file to a provided vector vec
	void read_data(std::string file, std::vector<point>& vec){
		std::ifstream fs(file);
		std::string data;
		while(std::getline(fs, data))
			vec.push_back(parse_line(data));
	}

	// prints point's coordinates
	std::string print_coords(double coords[COORD_NUM]){
		std::ostringstream oss;

		oss << '{';
		for(int i = 0; i < COORD_NUM; i++)
			oss << coords[i] << (i == COORD_NUM -1 ? "" : ", ");
		oss << '}';

		return oss.str();
	}

	// prints 3 columns of data
	void print3col(int col_dist, std::string s1, std::string s2, std::string s3){
		std::cout << std::fixed;
		std::cout << std::setw(col_dist) << std::left << s1 << std::setw(col_dist) << std::left << s2 << s3;
	}

}
