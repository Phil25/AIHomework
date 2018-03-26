#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "perc.h"

// number of coordinates in the data set
#define COORD_NUM 4

struct point{
	bool is_virginica;
	double coords[COORD_NUM];
};

std::vector<point> train_data;
std::vector<point> test_data;

double get_user_double(const double min, const double max){
	double input;
	do std::cin >> input;
	while(min > input || input > max);
	return input;
}

// training function
void train_perc(perc& p, std::vector<point>& data){

	// iterate through training data
	auto end = data.end();
	for(auto it = data.begin(); it != end; it++){

		// tune the result
		bool result = p.get(it->coords);
		p.tune(it->coords, it->is_virginica, result);

	}
}

point parse_line(std::string line){
	point p;
	std::istringstream iss(line);
	std::string data;

	// read coordinates
	int i = 0;
	while(std::getline(iss, data, ',') && i < COORD_NUM)
		p.coords[i++] = stod(data);

	// read class
	std::getline(iss, data);
	p.is_virginica = data.size() == 14;	

	return p;
}

void read_data(std::string file, std::vector<point>& vec){
	std::ifstream fs(file);
	std::string data;
	while(std::getline(fs, data))
		vec.push_back(parse_line(data));
}

int main(){

	// create perceptron class
	std::cout << "Provide learning parameter (0 < a < 1): ";
	double learning_param = get_user_double(0, 1);
	perc p(COORD_NUM, learning_param);

	std::cout << p << std::endl;

	// train it
	read_data("training.txt", train_data);
	train_perc(p, train_data);

	std::cout << p << std::endl;

	return 0;
}
