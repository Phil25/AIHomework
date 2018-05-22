#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <map>

#include "fraction.h"

// number of coordinates in the data set
#define ATTRIB_COUNT 7

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[0;36m"

#define BUYING_PRICE 0
#define MAINTENANCE_PRICE 1
#define DOOR_NUM 2
#define CAPACITY 3
#define LUGGAGE_SIZE 4
#define SAFETY 5
#define ACCEPTABILITY 6

#define COLOR_PROP COLOR_GREEN
#define COLOR_VAL COLOR_CYAN

// struct for holding the point;
struct car{
	// every attribute as a string
	std::array<std::string, ATTRIB_COUNT> attribs;

	static std::array<std::string, ATTRIB_COUNT> attribs_cols;

	// every unique type of the attribute
	static std::array<std::set<std::string>, ATTRIB_COUNT> attrib_sets;

	// number of unique values for each attribute
	static std::array<int, ATTRIB_COUNT> unique;

	// amount of appearances for every attribute of every type
	static std::array<std::map<std::string, int>, ATTRIB_COUNT> amount;

	friend std::ostream& operator<<(std::ostream&, const car&);

};

std::array<std::string, ATTRIB_COUNT> car::attribs_cols = {
	"Buying Price", "Maintenance Price", "Door Number", "Capacity", "Luggage Size", "Safety", "Acceptability"
};
std::array<std::set<std::string>, ATTRIB_COUNT> car::attrib_sets;
std::array<int, ATTRIB_COUNT> car::unique{0};
std::array<std::map<std::string, int>, ATTRIB_COUNT> car::amount;

namespace dr{
	void print_line(std::ostream& oss, std::string property, std::string value, std::string end){
		oss << COLOR_PROP << property << COLOR_RESET << ": " << COLOR_VAL << value << COLOR_RESET << end;
	}

	std::string format_prob(const std::string& name, const std::string& value, const fraction& frac){
		std::ostringstream oss;
		oss << "P(" << COLOR_PROP << name << COLOR_RESET << '=' << COLOR_VAL << value << COLOR_RESET << ") = " << frac;
		return oss.str();
	}

	std::string format_prob(const std::string& name, const std::string& value, const std::string& cond, const std::string& cond_value, const fraction& frac){
		std::ostringstream oss;
		oss << "P(";
		oss << COLOR_PROP << name << COLOR_RESET << '=' << COLOR_VAL << value << COLOR_RESET;
		oss << '|';
		oss << COLOR_PROP << cond << COLOR_RESET << '=' << COLOR_VAL << cond_value << COLOR_RESET;
		oss << ") = " << frac;
		return oss.str();
	}
}

std::ostream& operator<<(std::ostream& oss, const car& c){
	oss << '{';
	dr::print_line(oss, "b. price", c.attribs[BUYING_PRICE], ", ");
	dr::print_line(oss, "m. price", c.attribs[MAINTENANCE_PRICE], ", ");
	dr::print_line(oss, "door num", c.attribs[DOOR_NUM], ", ");
	dr::print_line(oss, "capacity", c.attribs[CAPACITY], ", ");
	dr::print_line(oss, "luggage", c.attribs[LUGGAGE_SIZE], ", ");
	dr::print_line(oss, "safety", c.attribs[SAFETY], ", ");
	dr::print_line(oss, "acceptability", c.attribs[ACCEPTABILITY], "");
	oss << '}';
	return oss;
}

namespace dr{

	// hidden readers
	namespace{
		std::string read(std::istringstream& iss){
			std::string data;
			std::getline(iss, data, ',');
			return data;
		}

		// parse line in a data set
		car parse_line(std::string& line){
			std::istringstream iss(line);

			car c{
				read(iss), // buying price
				read(iss), // maintenance price
				read(iss), // number of doors
				read(iss), // capacity
				read(iss), // luggage size
				read(iss), // safety
				read(iss), // acceptability
			};

			return c;
		}

	}

	// read a data file to a provided vector vec
	void read_data(std::string file, std::vector<car>& vec){
		std::ifstream fs(file);
		std::string data;
		//int limit = 0;
		while(std::getline(fs, data)){
			vec.push_back(parse_line(data));
			//if(++limit >= 10)
				//return;
		}
	}

	void inc_map(std::map<std::string, int>& m, std::string at){
		if(!m.count(at))
			m.insert(std::make_pair(at, 1));
		else m[at]++;
	}

	void calc_unique_values(std::vector<car>& data){

		// fill the sets
		auto end = data.end();
		for(auto it = data.begin(); it != end; it++)
			for(int i = 0; i < ATTRIB_COUNT; i++){
				car::attrib_sets[i].insert(it->attribs[i]);
				inc_map(car::amount[i], it->attribs[i]);
			}

		// get the unique values
		for(int i = 0; i < ATTRIB_COUNT; i++)
			car::unique[i] = car::attrib_sets[i].size();

	}

}
