#include <array>
#include <iomanip>
#include "graph.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[0;36m"

#define COLOR_PROP COLOR_GREEN
#define COLOR_VAL COLOR_CYAN

template <int S>
class sol{
	std::array<int, S +1> data;
	int dist = 0;

public:
	sol(){
		int i = 0;
		for(int& val : data)
			val = i++;
		data[S] = 0;
	}

	void set(const sol<S>& other){
		data = other.data;
	}

	void swap(int i, int j){
		int temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}

	int get_dist(const graph& g) const{
		int dist = 0;
		for(int i = 0; i < S; i++)
			dist += g(data[i], data[i+1]);
		return dist;
	}

	void operator=(int other){
		dist = other;
	}

	const int& operator()(int x) const{
		return data[x];
	}

	template <int SIZE>
	friend std::ostream& operator<<(std::ostream&, const sol<SIZE>&);

};

template <int S>
std::ostream& operator<<(std::ostream& os, const sol<S>& s){
	for(int i = 0; i < S; i++)
		os << COLOR_VAL << std::setfill(' ') << std::setw(2) << s.data[i] << COLOR_RESET << " -> ";
	os << COLOR_VAL << std::setfill(' ') << std::setw(2) << s.data[S] << COLOR_RESET;
	return os << "; " << COLOR_PROP << "dist" << COLOR_RESET << " = " << COLOR_VAL << s.dist << COLOR_RESET;
}
