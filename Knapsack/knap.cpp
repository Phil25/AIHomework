#include <iostream>
#include <chrono>

#include "data_reader.h"

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::high_resolution_clock::time_point t3;

//#define PRINT_FEASABLE

// find charasterictic vectors, with weight <= capacity
void get_feasible(std::vector<int>& char_vectors, int n, std::vector<item>& items, int capacity){
	unsigned long max = 1 << n; // 2^n
	for(unsigned long i = 0; i < max; i++)
		if(cv::get_weight(i, items, n) <= capacity)
			char_vectors.push_back(i);
}

int get_optimal(std::vector<int>& char_vectors, std::vector<item>& items, int n){
	int best_value = 0;
	int best_vector = 0;
	for(const int& vector : char_vectors){
		int value = cv::get_value(vector, items, n);
		if(value <= best_value)
			continue;
		best_vector = vector;
		best_value = value;
	}
	return best_vector;
}

int knapsack(std::vector<item>& items, int capacity, int n){
	std::vector<int> char_vectors;

	t1 = std::chrono::high_resolution_clock::now();
	// assign feasable solutions
	get_feasible(char_vectors, n, items, capacity);
	t2 = std::chrono::high_resolution_clock::now();

#ifdef PRINT_FEASABLE
	std::cout << "\n\t[FEASABLE]" << std::endl;
	for(const int& vector : char_vectors)
		std::cout << cv::print{vector, n, items} << std::endl;
#endif

	// get the most valuable combination
	return get_optimal(char_vectors, items, n);

}

int main(){

	std::vector<item> items;
	int capacity = dr::read_data("knapsack_data/13", items);
	//capacity = 70;
	int n = items.size();

	std::cout << "\n\t[INPUT]" << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout << "n: " << n << std::endl;
	for(auto i : items)
		std::cout << i << std::endl;

	int result = knapsack(items, capacity, n);
	t3 = std::chrono::high_resolution_clock::now();

	std::cout << "\n\t[SOLUTION]" << std::endl;
	std::cout << cv::print{result, n, items} << std::endl;

	std::cout << "\n\t[TIME]" << std::endl;
	auto dur_feasable = std::chrono::duration_cast<std::chrono::microseconds>(t2 -t1).count();
	auto dur_optimal = std::chrono::duration_cast<std::chrono::microseconds>(t3 -t2).count();
	std::cout << "Finding feasable: " << dur_feasable << std::endl;
	std::cout << "Finding optimal : " << dur_optimal << std::endl;

	return 0;
}
