#include <iostream>

#include "data_reader.h"

// generate characteristic vectors by incrementing 0-vector until overflow
void gen_char_vectors(std::vector<char_vector>& char_vectors, unsigned int n){
	unsigned long max = 2;
	unsigned long i = n-1;
	while(max *= 2, --i > 0);
	while(char_vectors.push_back(char_vector(n)), ++i < max);
}

// remove characteristic vectors based on the items vector and capacity
void filter(std::vector<char_vector>& char_vectors, std::vector<item>& items, int c){
	auto cv = char_vectors.begin();
	while(cv != char_vectors.end()){
		if(cv->sum_weights(items) > c)
			cv = char_vectors.erase(cv);
		else cv++;
	}
}

char_vector most_valuable(std::vector<char_vector>& char_vectors, std::vector<item>& items){
	int best_value = 0;
	char_vector* best_vector;
	std::cout << "\n\t[FILTERED]" << std::endl;
	for(char_vector& cv : char_vectors){
		int value = cv.sum_values(items);
		std::cout << cv << std::endl;
		if(value <= best_value)
			continue;
		best_vector = &cv;
		best_value = value;
	}
	return *best_vector;
}

char_vector knapsack(std::vector<item>& items, int capacity){
	// generate characteristic vectors
	std::vector<char_vector> char_vectors;
	gen_char_vectors(char_vectors, items.size());

	// filter out all unfeasable solutions
	filter(char_vectors, items, capacity);

	// get the most valueable combination
	return most_valuable(char_vectors, items);

}

int main(){

	std::vector<item> items;
	int capacity = dr::read_data("knapsack_data/13", items);
	capacity = 70;

	std::cout << "\n\t[INPUT]" << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	for(auto i : items)
		std::cout << i << std::endl;

	char_vector result = knapsack(items, capacity);
	std::cout << "\n\t[SOLUTION]" << std::endl;
	std::cout << result << std::endl;

	return 0;
}
