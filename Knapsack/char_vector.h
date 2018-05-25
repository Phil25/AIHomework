#include <ostream>
#include <vector>
#include <bitset>

#ifndef CHAR_VECTOR_H
#define CHAR_VECTOR_H

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[0;36m"

#define COLOR_PROP COLOR_GREEN
#define COLOR_VAL COLOR_CYAN

struct item{
	int weight, value;
};

std::ostream& operator<<(std::ostream& os, const item& i){
	os << '{';
	os << COLOR_PROP << "weight" << COLOR_RESET;
	os << '=';
	os << COLOR_VAL << i.weight << COLOR_RESET;
	os << ", ";
	os << COLOR_PROP << "value" << COLOR_RESET;
	os << '=';
	os << COLOR_VAL << i.value << COLOR_RESET;
	os << '}';
	return os;
}

class char_vector{
	static unsigned long last_vector;

	unsigned long vector;
	int weight = 0;
	int value = 0;
	int n = 0;

public:
	char_vector(int n):
		vector(last_vector++),
		weight(0),
		value(0),
		n(n)
	{}

	int sum_weights(std::vector<item>& items){
		weight = 0;
		for(int i = 0; i < n; i++)
			weight += items[i].weight *is_set(i);
		return weight;
	}

	int sum_values(std::vector<item>& items){
		value = 0;
		for(int i = 0; i < n; i++)
			value += items[i].value *is_set(i);
		return value;
	}

	bool operator<(const char_vector& other) const{
		return vector < other.vector;
	}

private:
	bool is_set(int at) const{
		return (vector >> at) &1;
	}

	friend std::ostream& operator<<(std::ostream&, const char_vector&);

};

unsigned long char_vector::last_vector = 0;

std::ostream& operator<<(std::ostream& os, const char_vector& cv){
	os << '{';
		os << COLOR_PROP << "vector" << COLOR_RESET;
		os << "={";
			for(int i = 0; i < cv.n; i++)
				os << cv.is_set(i);
		os << "}, ";
		os << COLOR_PROP << "weight" << COLOR_RESET;
		os << '=';
		os << COLOR_VAL << cv.weight << COLOR_RESET;
		os << ", ";
		os << COLOR_PROP << "value" << COLOR_RESET;
		os << '=';
		os << COLOR_VAL << cv.value << COLOR_RESET;
	os << '}';
	return os;
}


#endif
