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
	int value, weight;
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

namespace cv{
	bool is_set(int num, int at){
		return (num >> at) &1;
	}

	int get_weight(int vector, std::vector<item>& items, int n){
		int weight = 0;
		for(int i = 0; i < n; i++)
			weight += items[i].weight *is_set(vector, i);
		return weight;
	}

	int get_value(int vector, std::vector<item>& items, int n){
		int value = 0;
		for(int i = 0; i < n; i++)
			value += items[i].value *is_set(vector, i);
		return value;
	}

	struct print{
		int vector, n;
		std::vector<item>& items;
	};

	std::ostream& operator<<(std::ostream& os, const print& p){
		os << '{';
		os << COLOR_PROP << "vector" << COLOR_RESET;
		os << "={" << COLOR_VAL;;
			for(int i = 0; i < p.n; ++i)
				os << is_set(p.vector, i);
		os << COLOR_RESET << "}, ";
		os << COLOR_PROP << "weight" << COLOR_RESET;
		os << '=';
		os << COLOR_VAL << get_weight(p.vector, p.items, p.n) << COLOR_RESET;
		os << COLOR_RESET << ", ";
		os << COLOR_PROP << "value" << COLOR_RESET;
		os << '=';
		os << COLOR_VAL << get_value(p.vector, p.items, p.n) << COLOR_RESET;
		os << '}';
		return os;
	}
}

/*
 *
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
 */

#endif
