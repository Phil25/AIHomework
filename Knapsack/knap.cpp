#include <iostream>
#include <set>

#include "data_reader.h"

// generate characteristic vectors by incrementing 0-vector until overflow
void gen_char_vectors(std::set<char_vector>& char_vectors, int n){
	char_vector cvec;
	cvec.resize(n);
	do char_vectors.insert(cvec);
	while(cvec.increment());
}

// remove characteristic vectors based on the items vector and capacity
void filter(std::set<char_vector>& char_vectors, std::vector<item>& items, int c){
	for(auto cv : char_vectors)
		if(cv.sum_weights(items) > c)
			char_vectors.erase(cv);
}

char_vector most_valuable(std::set<char_vector>& char_vectors, std::vector<item>& items){
	int best_value = 0;
	char_vector best_vector;
	for(auto cv : char_vectors){
		int value = cv.sum_values(items);
		if(value <= best_value)
			continue;
		best_vector = cv;
		best_value = value;
	}
	return best_vector;
}

char_vector knapsack(std::vector<item>& items, int capacity){

	// generate characteristic vectors
	std::set<char_vector> char_vectors;
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

	std::cout << "Capacity: " << capacity << std::endl;
	for(auto i : items)
		std::cout << i << std::endl;

	char_vector result = knapsack(items, capacity);
	std::cout << result << std::endl;

	return 0;
}
