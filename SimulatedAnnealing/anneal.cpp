#include <iostream>
#include <math.h>

#include "data_reader.h"
#include "sol.h"

#define TEST

#ifdef TEST
#define SIZE 15
#define PATH "./tsp_data/tsp_data.txt"
#else
#define SIZE 42
#define PATH "./tsp_data/tsp_data2.txt"
#endif

#define THRESHOLD 0.025
#define HEAT 1000
#define ITERATION_LIMIT 100
#define UNCHANGED_ITERATION_LIMIT 5

double probability(int curr, int cand, double heat){
	return std::exp(-std::abs(curr -cand) /heat);
}

double cooling(double heat){
	return heat /1.1;
}

int rand(int min, int max){
	int static seed = std::time(0);
	std::srand(seed++);
	return rand() %(max -min + 1) +min;
}

bool change_neighbour(sol<SIZE>& s, const graph& g, double& heat){
	static int ITERATION = 0;
	static int UNCHANGED_ITERATIONS = 0;

	int curr_dist = s.get_dist(g);
	int cand = rand(1, SIZE -2);

	std::cout << std::endl << "\tITERATION " << ++ITERATION << std::endl;
	std::cout << COLOR_PROP << "   Checking" << COLOR_RESET << ": " << (s = curr_dist, s) << std::endl;

	sol<SIZE> other(s);
	other.swap(cand, cand+1);
	int cand_dist = other.get_dist(g);

	std::cout << COLOR_PROP << "  Neighbour" << COLOR_RESET << ": " << (other = cand_dist, other) << std::endl;

	double prob = probability(curr_dist, cand_dist, heat);
	heat = cooling(heat);

	std::cout << COLOR_PROP << "Probability" << COLOR_RESET << ": " << COLOR_VAL << prob << COLOR_RESET << std::endl;
	std::cout << COLOR_PROP << "       Heat" << COLOR_RESET << ": " << COLOR_VAL << heat << COLOR_RESET << std::endl;

	if(prob >= THRESHOLD){
		s.set(other);
		UNCHANGED_ITERATIONS = 0;
	}else UNCHANGED_ITERATIONS++;

	return UNCHANGED_ITERATIONS < UNCHANGED_ITERATION_LIMIT && ITERATION < ITERATION_LIMIT;
}

void tsp_climb(const graph& g){
	double heat = HEAT;
	sol<SIZE> s;
	while(change_neighbour(s, g, heat));
}

int main(){
	graph g(SIZE);
	dr::read_data(PATH, g);
	tsp_climb(g);
	return 0;
}
