#include <algorithm>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

// number of coordinates in the data set
#define COORD_NUM 4

// struct for holding the point;
struct point{
	std::string iris;
	double coords[COORD_NUM];
	double distance;

	bool operator<(const point& other){
		return this->distance < other.distance;
	}
};

// comp struct for comparing points in priority queue
struct comp{
	bool operator()(point& a, point& b){
		return a.distance > b.distance;
	}
};

// vectors storing train and test data
std::vector<point> train_data;
std::vector<point> test_data;

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

// calculate distance between two points
double dist(point& p1, point& p2){
	double dist = 0.0;
	double to_sqr = 0.0;
	for(int i = 0; i < COORD_NUM; i++){
		to_sqr = p1.coords[i] -p2.coords[i];
		dist += to_sqr *to_sqr;
	}
	return dist;
}

// the general knn algorithm
std::string knn(std::vector<point>& vec, point& p, int k){
	std::priority_queue<point, std::vector<point>, comp> pq;

	// iterate though train data vector
	auto end_vec = vec.end();
	for(auto it = vec.begin(); it != end_vec; it++){

		// calculate distance to test point p
		it->distance = dist(*it, p);

		// push train data point to a priority queue using distance as weight
		pq.push(*it);
	}

	std::map<std::string, int> m;
	std::string iris = "";
	std::string top_iris = "<none>";
	int top_appear = 0;

	// take out k elements from the priority queue
	for(int i = 0; i < k; pq.pop(), i++){
		// count appearance of individual elements
		iris = pq.top().iris;
		m[iris]++;

		// keep track of most common one
		if(m[iris] > top_appear){
			top_iris = iris;
			top_appear = m[iris];
		}
	}

	return top_iris;
}

// calculate k neighbours
void test_for_k(int k){
	int all = 0, correct = 0;
	print3col(25, "COORDINATES", "CORRECT", "PREDICTED");
	std::cout << std::endl;

	// iterate through test data
	for(auto it = test_data.begin(); it != test_data.end(); it++){

		// get the prediction
		std::string predicted = knn(train_data, *it, k);

		// print info
		print3col(25, print_coords(it->coords), it->iris, predicted);
		
		// mark incorrect guesses
		bool is_correct = it->iris == predicted;
		if(!is_correct)
			std::cout << " (!)";

		std::cout << std::endl;

		// keep track of correctly guessed entries
		correct += is_correct;
		all++;
	}

	// print accuracy for a particular k
	std::cout << "Accuracy for " << k << ": " << ((double)correct/all)*100 << "%" << std::endl;
}

void input_coords();
void plot_percentage();

int main(){

	// parse assignment files
	read_data("train.txt", train_data);
	read_data("test.txt", test_data);
	std::sort(train_data.begin(), train_data.end());

	// read k from user
	int k;
	std::cout << "Input K: ";
	std::cin >> k;

	// test
	test_for_k(k);

	// core loop
	int option;
	while(1){
		std::cout << std::endl << "Exit (0), input test coordinates (1) or plot accuracy percentage (2): ";
		std::cin >> option;
		switch(option){
			case 0: return 0;
			case 1: input_coords(); break;
			case 2: plot_percentage(); break;
		}
	}

	return 0;
}

void input_coords(){
	int k = 0;
	point p;

	// get new K
	std::cout << "Input new K: ";
	std::cin >> k;
	if(k <= 0)
		return;

	// get new point data
	std::cout << "Input test coordinates: ";
	for(int i = 0; i < COORD_NUM; i++)
		std::cin >> p.coords[i];

	// create and process point
	std::cout << "Predicted for " << print_coords(p.coords) << ": " << knn(train_data, p, k) << std::endl;
}

void plot_percentage(){
	// read range
	int min, max;
	std::cout << "Enter range of k (inclusive): ";
	std::cin >> min >> max;

	// set up variables
	int correct = 0;
	std::string predicted = "";
	const int all = test_data.size();
	const auto end = test_data.end();

	// iterate through test_data for every k
	std::cout << "Accuracy plot for range of k [" << min << ", " << max << "]:" << std::endl;
	for(int k = min; k <= max; k++){
		std::cout << std::setw(5) << std::left << k;
		correct = 0;
		for(auto it = test_data.begin(); it != end; it++)
			correct += knn(train_data, *it, k) == it->iris;
		int i = 0;
		std::cout << '|';
		for(; i < correct; i++)
			std::cout << '*';
		for(; i < all; i++)
			std::cout << '.';
		std::cout << "| " << ((double)correct/all*100) << "%" << std::endl;
	}
}
