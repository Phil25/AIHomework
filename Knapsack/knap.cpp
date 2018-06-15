#include <iostream>
#include <chrono>

#include "data_reader.h"

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;

int knapsack(std::vector<item>& items, int capacity, int n){

	unsigned long max = 1 << n;
	int best_value = 0;
	int best_vector = 0;
	for(unsigned long vector = 1; vector < max; vector++){

		// skip non-feasable vectors
		if(cv::get_weight(vector, items, n) > capacity)
			continue;

		// skip if current vector doesn't have the best value
		int value = cv::get_value(vector, items, n);
		if(value <= best_value)
			continue;

		// save a feasable vector of best value
		best_vector = vector;
		best_value = value;

	}

	return best_vector;
}

int main(){

	std::vector<item> items;
	int capacity = dr::read_data("knapsack_data/14", items);
	//capacity = 70;
	int n = items.size();

	std::cout << "\n\t[INPUT]" << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout << "n: " << n << std::endl;
	for(auto i : items)
		std::cout << i << std::endl;

	t1 = std::chrono::high_resolution_clock::now();
	int result = knapsack(items, capacity, n);
	t2 = std::chrono::high_resolution_clock::now();

	std::cout << "\n\t[SOLUTION]" << std::endl;
	std::cout << cv::print{result, n, items} << std::endl;

	std::cout << "\n\t[TIME]" << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 -t1).count();
	std::cout << "Duration: " << duration << std::endl;

	return 0;
}
