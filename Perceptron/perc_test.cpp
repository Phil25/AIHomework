#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "perc.h"

// number of coordinates in the data set
#define COORD_NUM 4

struct point{
	bool is_virginica;
	double coords[COORD_NUM];
};

std::vector<point> train_data;
std::vector<point> test_data;

template <typename T>
T get_user_num(const T min, const T max){
	T input;
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

std::string get_iris(bool is_virginica){
	return is_virginica ? "virginica" : "versicolor";
}

std::string get_coords(double coords[COORD_NUM]){
	std::ostringstream oss;

	oss << '{';
	for(int i = 0; i < COORD_NUM; i++)
		oss << coords[i] << (i == COORD_NUM -1 ? "" : ", ");
	oss << '}';

	return oss.str();
}

void print3col(int col_dist, std::string s1, std::string s2, std::string s3){
	std::cout << std::fixed;
	std::cout << std::setw(col_dist) << std::left << s1 << std::setw(col_dist) << std::left << s2 << s3;
}

int main(){

	// input the learning parameter
	std::cout << "Provide learning parameter (0 < a < 1): ";
	double learning_param = get_user_num<double>(0, 1);

	// input number of iterations
	std::cout << "Provide number of iterations for training: ";
	int training_iterations = get_user_num<int>(0, 999999);

	// create perceptron class
	perc p(COORD_NUM, learning_param);

	// train it
	read_data("training.txt", train_data);
	for(int i = 0; i < training_iterations; i++)
	train_perc(p, train_data);

	// read test data
	read_data("test.txt", test_data);

	// prepare table column names
	print3col(25, "COORDINATES", "CORRECT", "PREDICTED");
	std::cout << std::endl;

	// iterate through test data
	auto end = test_data.end();
	for(auto it = test_data.begin(); it != end; it++){

		// call the aglorithm
		bool correct = it->is_virginica;
		bool predicted = p.get(it->coords);
		print3col(25, get_coords(it->coords), get_iris(correct), get_iris(predicted));

		// mark incorrect guesses
		if(correct != predicted)
			std::cout << " (!)";

		std::cout << std::endl;
	}

	return 0;
}
