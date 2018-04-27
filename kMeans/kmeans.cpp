#include "data_reader.h"
#include <ctime>

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
			std::cout << old_owner << " -> " << it->owner << " @ " << to_str(it->coords) << std::endl;
		}
	}
	return assigns_made;
}

void kmeans(const int k, pvector& data){
	// randomize initial clusters
	loop_data(data, it)
		it->owner = rand(k);

	// initialize vector of clusteroids and their number of points
	cvector clusteroids;
	ivector count;

	// main k-means loop
	bool assigns_made = false;
	int iter_count = 0;
	do{
		std::cout << "=============" << std::endl;
		std::cout << "ITERATION: " << ++iter_count << std::endl;
		assigns_made = false;

		reset_cluster_data(clusteroids, count, k);

		find_clusters(data, clusteroids, count, k);

		if(reassign_points(data, clusteroids, k))
			assigns_made = true;

	}while(assigns_made);
}

int main(){
	// parse test file
	std::vector<point> data;
	dr::read_data("test.txt", data);

	// read k from user
	int k = 3;
	//std::cout << "Number of clusters: ";
	//std::cin >> k;

	kmeans(k, data);

}
