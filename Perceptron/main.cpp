#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "perc.h"

// number of coordinates in the data set
#define COORD_NUM 4

// structure for iris
struct point{
	bool is_virginica;
	double coords[COORD_NUM];
};

// helper function declarations
void read_data(std::string file, std::vector<point>& vec);
point parse_line(std::string);
std::string get_iris(bool);
std::string get_coords(double[COORD_NUM]);
void print3col(int col_dist, std::string, std::string, std::string);
template <typename T> T get_user_num(const T min, const T max);

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

void test_perc(perc& p, std::vector<point>& data){
	print3col(25, "COORDINATES", "CORRECT", "PREDICTED");
	std::cout << std::endl;

	// iterate through the training set
	int correct = 0, all = 0;
	auto end = data.end();
	for(auto it = data.begin(); it != end; it++){

		// call the aglorithm
		bool actual = it->is_virginica;
		bool predicted = p.get(it->coords);
		print3col(25, get_coords(it->coords), get_iris(actual), get_iris(predicted));

		// mark incorrect guesses
		if(actual != predicted)
			std::cout << " (!)";
		else correct++;

		all++;
		std::cout << std::endl;
	}

	double accuracy = (double)correct/all *100;
	std::cout << "Accuracy: " << accuracy << '%' << std::endl;
}

void input_loop(perc& p){
	double test_coords[COORD_NUM];
	while(1){
		std::cout << std::endl << "Enter coordinates: " << std::endl;
		int i = 0;
		while(i < COORD_NUM)
			std::cin >> test_coords[i++];
		std::cout << "Prediction: " << get_iris(p.get(test_coords)) << std::endl;
	}
}

int main(){
	std::vector<point> train_data;
	std::vector<point> test_data;

	// input the learning parameter
	std::cout << "Learning parameter (0 < a < 1): ";
	double learning_param = get_user_num<double>(0, 1);

	// input number of iterations
	std::cout << "Number of training iterations: ";
	int training_iterations = get_user_num<int>(0, 999999);

	// create perceptron class
	perc p(COORD_NUM, learning_param);

	// train it k times
	read_data("training.txt", train_data);
	for(int i = 0; i < training_iterations; i++)
		train_perc(p, train_data);

	// test it
	read_data("test.txt", test_data);
	test_perc(p, test_data);

	// run the user test input loop
	input_loop(p);

	return 0;
}

// helper functions

inline void read_data(std::string file, std::vector<point>& vec){
	std::ifstream fs(file);
	std::string data;
	while(std::getline(fs, data))
		vec.push_back(parse_line(data));
}

inline point parse_line(std::string line){
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

inline std::string get_iris(bool is_virginica){
	return is_virginica ? "virginica" : "versicolor";
}

inline std::string get_coords(double coords[COORD_NUM]){
	std::ostringstream oss;

	oss << '{';
	for(int i = 0; i < COORD_NUM; i++)
		oss << coords[i] << (i == COORD_NUM -1 ? "" : ", ");
	oss << '}';

	return oss.str();
}

inline void print3col(int col_dist, std::string s1, std::string s2, std::string s3){
	std::cout << std::fixed;
	std::cout << std::setw(col_dist) << std::left << s1 << std::setw(col_dist) << std::left << s2 << s3;
}

template <typename T>
inline T get_user_num(const T min, const T max){
	T input;
	do std::cin >> input;
	while(min > input || input > max);
	return input;
}

