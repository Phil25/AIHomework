#include "data_reader.h"
#include <ctime>

#define loop_data(data, it)\
	for(auto it = data.begin(); it != data.end(); it++)
// ^ unoptimized -- data.end() executed every iteration :c

// vector of clusters
typedef std::vector<std::array<double, COORD_NUM>> cvector;
typedef std::vector<int> ivector;
typedef std::vector<point> pvector;
//typedef std::vector<point>::iterator piter;

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
	loop_data(data, it){
		for(int i = 0; i < COORD_NUM; i++)
			clusteroids[it->owner][i] += it->coords[i];
		count[it->owner]++;
	}

	// divide to get the average
	for(int i = 0; i < k; i++)
		clusteroids[k][i] /= count[k];
}

void kmeans(const int k, pvector& data){
	// randomize initial clusters
	loop_data(data, it)
		it->owner = rand(k);

	// initialize vector of clusteroids and their number of points
	cvector clusteroids;
	ivector count;

	// main k-means loop
	bool changed = false;
	do{
		changed = false;
		reset_cluster_data(clusteroids, count, k);
		find_clusters(data, clusteroids, count, k);
		// TODO: reassign points and stuff

	}while(changed);
}

int main(){
	// parse test file
	std::vector<point> data;
	dr::read_data("test.txt", data);

	// read k from user
	int k;
	std::cout << "Number of clusters: ";
	std::cin >> k;

	kmeans(k, data);

}
