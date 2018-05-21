#include "data_reader.h"
#include <ctime>

//#define TEST

#define loop_data(data, it)\
	for(auto it = data.begin(); it != data.end(); it++)\
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

void count_points(pvector& data, int* count, int size){
	for(int i = 0; i < size; i++)
		count[i] = 0;
	loop_data(data, it)
		count[it->owner]++;
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

double distsqr(point& p1, point& p2){
	return distsqr(p1.coords, p2.coords);
}

double get_inner_dist(pvector& data, darray& centroid, int i){
	double dist = 0.0;
	loop_data(data, it)
		if(it->owner == i)
			dist += distsqr(it->coords, centroid);
	return dist;
}

void print_cluster_info(pvector& data, cvector& centroids, int k){
	int count[k];
	count_points(data, count, k);

	std::cout << "=== CLUSTER INFO ===" << std::endl;
	for(int i = 0; i < k; i++){
		std::cout << "Cluster #" << i << ":" << std::endl;
		std::cout << "    " << "vector: " << to_str(centroids[i]) << std::endl;
		std::cout << "    " << "point count: " << count[i] << std::endl;
		std::cout << "    " << "inner dist: " << get_inner_dist(data, centroids[i], i) << std::endl;
	}
	std::cout << "====================" << std::endl;
}

// random integer between 0 and max-1 inclusive
int rand(int max){
	static int seed = std::time(NULL);
	std::srand(++seed);
	int result = (double)std::rand() /RAND_MAX *max;
	return result;
}

void reset_cluster_data(cvector& centroids, ivector& count, int k){
	centroids.clear();
	count.clear();
	for(int i = 0; i < k; i++){
		centroids.push_back(std::array<double, COORD_NUM>());
		count.push_back(0);
	}
}

void find_clusters(pvector& data, cvector& centroids, ivector& count, int k){
	// sum up all coords
	loop_data(data, it){
		for(int i = 0; i < COORD_NUM; i++)
			centroids[it->owner][i] += it->coords[i];
		count[it->owner]++;
	}

	for(int i = 0; i < k; i++)
		std::cout << i << ". Count: " << count[i] << std::endl;

	// divide to get the average
	for(int i = 0; i < k; i++)
		for(int j = 0; j < COORD_NUM; j++)
			centroids[i][j] /= count[i];
}

int get_closest_centroid(darray& coords, cvector& centroids, int k){
	int closest_id = 0;
	double closest_dist = 999999999999999999.0;
	for(int i = 0; i < k; i++){
		double dist = distsqr(coords, centroids[i]);
		if(dist >= closest_dist)
			continue;
		closest_dist = dist;
		closest_id = i;
	}
	return closest_id;
}

bool reassign_points(pvector& data, cvector& centroids, int k){
	bool assigns_made = false;
	loop_data(data, it){
		int old_owner = it->owner;
		it->owner = get_closest_centroid(it->coords, centroids, k);
		if(old_owner != it->owner){
			assigns_made = true;
			std::cout << old_owner << " -> " << it->owner << " for " << to_str(it->coords) << std::endl;
		}
	}
	if(!assigns_made)
		std::cout << "No changes..." << std::endl << std::endl;
	return assigns_made;
}

// single kmeans iteration
bool iteration(pvector& data, cvector& centroids, int k){
	// vector of amount of points for every centroid
	static ivector count;

	static int iter_count = 0;
	std::cout << "\n\n=========================" << std::endl;
	std::cout << "ITERATION: " << ++iter_count << std::endl;
	std::cout << "=========================" << std::endl;

	reset_cluster_data(centroids, count, k);
	find_clusters(data, centroids, count, k);
	bool assigns_made = reassign_points(data, centroids, k);

	print_cluster_info(data, centroids, k);

	return assigns_made;
}

void input_loop(int k){
	// vector of centroids
	cvector centroids;
	point p;

	// get new point data
	std::cout << "\nInput test coordinates: ";
	for(int i = 0; i < COORD_NUM; i++)
		std::cin >> p.coords[i];

	int i = get_closest_centroid(p.coords, centroids, k);
	std::cout << to_str(p.coords) << " assigned to " << i << '.' << std::endl;
}

void kmeans(pvector& data, int k){
	// vector of centroids
	cvector centroids;

	// randomize initial clusters
	loop_data(data, it)
		it->owner = rand(k);

	// main k-means loop
	while(iteration(data, centroids, k));

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

	kmeans(data, k);

	while(1)
		input_loop(k);

}
