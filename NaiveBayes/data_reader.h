#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <set>

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

typedef std::array<std::string, ATTRIB_COUNT> str7;
typedef std::array<int, ATTRIB_COUNT> int7;

// struct for holding the point;
struct car{
	// every attribute as a string
	std::array<std::string, ATTRIB_COUNT> attribs;

	// number of unique values for each attribute
	static std::array<int, ATTRIB_COUNT> unique;

	friend std::ostream& operator<<(std::ostream&, const car&);

};

int7 car::unique{0};

// hidden cout wrappers
namespace{
	void print_line(std::ostream& oss, std::string property, std::string value, std::string end){
		oss << COLOR_PROP << property << COLOR_RESET << ": " << COLOR_VAL << value << COLOR_RESET << end;
	}
}

std::ostream& operator<<(std::ostream& oss, const car& c){
	oss << '{';
	print_line(oss, "b. price", c.attribs[BUYING_PRICE], ", ");
	print_line(oss, "m. price", c.attribs[MAINTENANCE_PRICE], ", ");
	print_line(oss, "door num", c.attribs[DOOR_NUM], ", ");
	print_line(oss, "capacity", c.attribs[CAPACITY], ", ");
	print_line(oss, "luggage", c.attribs[LUGGAGE_SIZE], ", ");
	print_line(oss, "safety", c.attribs[SAFETY], ", ");
	print_line(oss, "acceptability", c.attribs[ACCEPTABILITY], "");
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
		while(std::getline(fs, data))
			vec.push_back(parse_line(data));
	}

	void calc_unique_values(std::vector<car>& data){

		// sets for each attribute
		std::array<std::set<std::string>, ATTRIB_COUNT> sets;

		// fill the sets
		auto end = data.end();
		for(auto it = data.begin(); it != end; it++)
			for(int i = 0; i < ATTRIB_COUNT; i++)
				sets[i].insert(it->attribs[i]);

		// get the unique values
		for(int i = 0; i < ATTRIB_COUNT; i++)
			car::unique[i] = sets[i].size();
	}

}
