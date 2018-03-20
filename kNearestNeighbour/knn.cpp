#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

#define COORD_NUM 4

struct point{
	std::string iris;
	double coords[COORD_NUM];
	double distance;
};

struct comp{
	bool operator()(point& a, point& b){
		return a.distance > b.distance;
	}
};

std::vector<point> train_data;
std::vector<point> test_data;

std::string print_point(point& p){
	std::ostringstream oss;
	oss << '{';
	for(int i = 0; i < COORD_NUM; i++)
		oss << p.coords[i] << (i == COORD_NUM -1 ? "" : ", ");
	oss << '}';
	return oss.str();
}

point parse_line(std::string& line){
	point p;
	std::istringstream iss(line);
	std::string data;

	int i = 0;
	while(std::getline(iss, data, ',') && i < COORD_NUM)
		p.coords[i++] = stod(data);

	std::getline(iss, data);
	p.iris = data;

	return p;
}

void read_data(std::string file, std::vector<point>& vec){
	std::ifstream fs(file);
	std::string data;
	while(std::getline(fs, data))
		vec.push_back(parse_line(data));
}

double dist(point& p1, point& p2){
	double dist = 0.0;
	double to_sqr = 0.0;
	for(int i = 0; i < COORD_NUM; i++){
		to_sqr = p1.coords[i] -p2.coords[i];
		dist += to_sqr *to_sqr;
	}
	return dist;
}

std::string knn(std::vector<point>& vec, point& p, int k){
	std::priority_queue<point, std::vector<point>, comp> pq;

	auto end_vec = vec.end();
	for(auto it = vec.begin(); it != end_vec; it++){
		it->distance = dist(*it, p);
		pq.push(*it);
	}

	std::map<std::string, int> m;
	for(int i = 0; i < k; pq.pop(), i++)
		m[pq.top().iris]++;

	std::string top_class = "<none>";
	int top_appear = 0;
	auto end_map = m.end();
	for(auto it = m.begin(); it != end_map; it++){
		if(it->second <= top_appear)
			continue;
		top_appear = it->second;
		top_class = it->first;
	}

	return top_class;
}

void print3col(int col_dist, std::string s1, std::string s2, std::string s3){
	std::cout << s1 << std::setw(col_dist -s1.length()) << s2 << std::setw(col_dist -s2.length()) << s3 << std::endl;
}

void test_for_k(int k){
	int all = 0, correct = 0;
	//print3col(50, "Coordinates", "Correct", "Predicted");
	for(auto it = test_data.begin(); it != test_data.end(); it++){
		//print3col(50, print_point(*it), it->iris, knn(train_data, *it, 5));
		correct += it->iris == knn(train_data, *it, k);
		all++;
	}
	std::cout << "Accuracy for " << k << ": " << ((double)correct/all)*100 << "%" << std::endl;
}

int main(){
	read_data("train.txt", train_data);
	read_data("test.txt", test_data);

	for(int i = 1; i < 100; i++)
		test_for_k(i);

	return 0;
}
