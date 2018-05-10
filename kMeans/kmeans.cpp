#include "data_reader.h"
#include <ctime>

//#define TEST

#define loop_data(data, it)\
	for(auto it = data.begin(); it != data.end(); it++)
// ^ unoptimized -- data.end() executed every iteration :c

// vector of clusters
typedef std::array<double, COORD_NUM> darray;
typedef std::vector<darray> cvector;
typedef std::vector<int> ivector;
typedef std::vector<point> pvector;

std::string to_str(darray& arr){
	std::ostringstream oss;
	oss << '{';
	for(int i = 0; i < COORD_NUM; i++){
		oss << arr[i];
		if(i != COORD_NUM -1)
			oss << ", ";
	}
	oss << '}';
	return oss.str();
}

double distsqr(darray& p1, darray& p2){
	double result = 0.0;
	double temp = 0.0;
	for(int i = 0; i < COORD_NUM; i++){
		temp = p2[i] -p1[i];
		result += temp *temp;
	}
	return result;
}

// random integer between 0 and max-1 inclusive
int rand(int max){
	static int seed = std::time(NULL);
	std::srand(++seed);
	int result = (double)std::rand() /RAND_MAX *max;
	return result;
}

void reset_cluster_data(cvector& clusteroids, ivector& count, int k){
	clusteroids.clear();
	count.clear();
	for(int i = 0; i < k; i++){
		clusteroids.push_back(std::array<double, COORD_NUM>());
		count.push_back(0);
	}
}

void find_clusters(pvector& data, cvector& clusteroids, ivector& count, int k){
	// sum up all coords
	loop_data(data, it){
		for(int i = 0; i < COORD_NUM; i++)
			clusteroids[it->owner][i] += it->coords[i];
		count[it->owner]++;
	}

	// divide to get the average
	for(int i = 0; i < k; i++)
		for(int j = 0; j < COORD_NUM; j++)
			clusteroids[i][j] /= count[i];
}

int get_closest_clusteroid(darray& coords, cvector& clusteroids, int k){
	int closest_id = 0;
	double closest_dist = 999999999999999999.0;
	for(int i = 0; i < k; i++){
		double dist = distsqr(coords, clusteroids[i]);
		if(dist > closest_dist)
			continue;
		closest_dist = dist;
		closest_id = i;
	}
	return closest_id;
}

bool reassign_points(pvector& data, cvector& clusteroids, int k){
	bool assigns_made = false;
	loop_data(data, it){
		int old_owner = it->owner;
		it->owner = get_closest_clusteroid(it->coords, clusteroids, k);
		if(old_owner != it->owner){
			assigns_made = true;
			std::cout << old_owner << " -> " << it->owner << " for " << to_str(it->coords) << std::endl;
		}
	}
	return assigns_made;
}

void print_sums(pvector& data, int k){
}

bool iteration(pvector& data, cvector& clusteroids, int k){
	// vector of amount of points for every clusteroid
	static ivector count;

	static int iter_count = 0;
	std::cout << "\nITERATION: " << ++iter_count << std::endl;

	reset_cluster_data(clusteroids, count, k);

	find_clusters(data, clusteroids, count, k);

	print_sums(data, k);

	return reassign_points(data, clusteroids, k);
}

void input_loop(int k, cvector& clusteroids){
	point p;

	// get new point data
	std::cout << "\nInput test coordinates: ";
	for(int i = 0; i < COORD_NUM; i++)
		std::cin >> p.coords[i];

	int i = get_closest_clusteroid(p.coords, clusteroids, k);
	std::cout << to_str(p.coords) << " assigned to " << i << '.' << std::endl;
}

int main(){
	// parse test file
	pvector data;
	dr::read_data("train.txt", data);

	// read k from user
	int k = 3;
#ifndef TEST
	std::cout << "Number of clusters: ";
	std::cin >> k;
#endif

	// vector of clusteroids
	cvector clusteroids;

	// randomize initial clusters
	loop_data(data, it)
		it->owner = rand(k);

	// main k-means loop
	while(iteration(data, clusteroids, k));
	std::cout << "No changes..." << std::endl;

	while(1)
		input_loop(k, clusteroids);

}
