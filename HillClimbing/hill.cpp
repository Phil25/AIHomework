#include <iostream>

#include "data_reader.h"
#include "sol.h"

//#define TEST

#ifdef TEST
#define SIZE 15
#define PATH "./tsp_data/tsp_data.txt"
#else
#define SIZE 42
#define PATH "./tsp_data/tsp_data2.txt"
#endif

bool change_neighbour(sol<SIZE>& s, const graph& g){
	static int ITERATION = 0;
	int reassignment = 0;

	int best_swap = -1;
	int best_dist = s.get_dist(g);

	std::cout << std::endl << "\tITERATION " << ++ITERATION << std::endl;
	std::cout << COLOR_PROP << " Checking: " << COLOR_RESET << (s = best_dist, s) << std::endl;

	// Iterate all swap possiblities
	for(int i = 1; i < SIZE -2; i++){
		sol<SIZE> other(s);
		other.swap(i, i+1);

		int other_dist = other.get_dist(g);
		if(other_dist >= best_dist)
			continue;

		std::cout << COLOR_PROP << "Assign" << COLOR_RESET << " #" << (++reassignment) << ": " << (other = other_dist, other) << std::endl;
		best_dist = other_dist;
		best_swap = i;
	}

	// No better neighbour found
	if(best_swap == -1)
		return false;

	sol<SIZE> best(s);
	best.swap(best_swap, best_swap +1);

	std::cout << COLOR_PROP << "  Swapped: " << COLOR_RESET;
	for(int i = 0; i < best_swap; i++)
		std::cout << "      ";
	std::cout << COLOR_RED << " ^     ^" << COLOR_RESET << std::endl;;

	s.set(best);
	return true;
}

void tsp_climb(const graph& g){
	sol<SIZE> s;
	s.rand_shuffle();
	while(change_neighbour(s, g));
}

int main(){
	graph g(SIZE);
	dr::read_data(PATH, g);
	tsp_climb(g);
	return 0;
}
