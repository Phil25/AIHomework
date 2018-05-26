#include <iostream>

#include "data_reader.h"

// find charasterictic vectors, with weight <= capacity
void get_feasible(std::vector<int>& char_vectors, int n, std::vector<item>& items, int capacity){
	unsigned long max = 2;
	unsigned long i = n-1;
	while(max *= 2, --i > 0);
	while(++i < max)
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

	// assign feasable solutions
	get_feasible(char_vectors, n, items, capacity);

	std::cout << "\n\t[FEASABLE]" << std::endl;
	for(const int& vector : char_vectors)
		std::cout << cv::print{vector, n} << std::endl;

	// get the most valuable combination
	return get_optimal(char_vectors, items, n);

}

void print_bin(int num, int size){
	for(int i = 0; i < size; i++)
		std::cout << cv::is_set(num, i);
	std::cout << std::endl;
}

int main(){

	std::vector<item> items;
	int capacity = dr::read_data("knapsack_data/13", items);
	capacity = 70;
	int n = items.size();

	std::cout << "\n\t[INPUT]" << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout << "n: " << n << std::endl;
	for(auto i : items)
		std::cout << i << std::endl;

	int result = knapsack(items, capacity, n);
	std::cout << "\n\t[OPTIMAL]" << std::endl;
	std::cout << cv::print{result, n} << std::endl;
	std::cout << "Weight: " << cv::get_weight(result, items, n) << std::endl;
	std::cout << "Value: " << cv::get_value(result, items, n) << std::endl;

	return 0;
}
