#include <ostream>
#include <vector>

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

struct char_vector : public std::vector<bool>{
	int weight = 0;
	int value = 0;
	int n = 0;

	void resize(int new_size){
		std::vector<bool>::resize(new_size);
		n = new_size;
	}

	// binary increment vector of bools, (001 -> 010)
	// returns false when overflow
	bool increment(){
		int i = -1;
		do i++, operator[](i) = !operator[](i);
		while(i < n && !operator[](i));
		return i != n;
	}

	int sum_weights(std::vector<item>& items){
		weight = 0;
		for(int i = 0; i < n; i++)
			weight += items[i].weight *operator[](i);
		return weight;
	}

	int sum_values(std::vector<item>& items){
		value = 0;
		for(int i = 0; i < n; i++)
			value += items[i].value *operator[](i);
		return value;
	}
};

std::ostream& operator<<(std::ostream& os, const char_vector& cv){
	os << '{';
		os << COLOR_PROP << "vector" << COLOR_RESET;
		os << "={";
			os << COLOR_VAL;
			for(bool b : cv)
				os << b;
			os << COLOR_RESET;
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
