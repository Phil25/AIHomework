#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

// number of coordinates in the data set
#define ATTRIB_COUNT 7

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_CYAN "\033[0;36m"

#define COLOR_PROP COLOR_GREEN
#define COLOR_VAL COLOR_CYAN

typedef std::array<int, ATTRIB_COUNT> int7;

// struct for holding the point;
struct car{
	typedef std::string str;

	str buying_price;
	str maintenance_price;
	int door_num;
	int capacity;
	str luggage_size;
	str safety;
	str acceptability;
	
	// number of different values for each attribute
	static int7 diff_vals;
	friend std::ostream& operator<<(std::ostream&, const car&);

};

int7 car::diff_vals{0};

std::ostream& operator<<(std::ostream& oss, const car& c){
	oss << '{';
	oss << COLOR_PROP << "b. price" << COLOR_RESET << ": " << COLOR_VAL << c.buying_price << COLOR_RESET << ", ";
	oss << COLOR_PROP << "m. price" << COLOR_RESET << ": " << COLOR_VAL << c.maintenance_price << COLOR_RESET << ", ";
	oss << COLOR_PROP << "door num" << COLOR_RESET << ": " << COLOR_VAL << c.door_num << COLOR_RESET << ", ";
	oss << COLOR_PROP << "capacity" << COLOR_RESET << ": " << COLOR_VAL << c.capacity << COLOR_RESET << ", ";
	oss << COLOR_PROP << "luggage" << COLOR_RESET << ": " << COLOR_VAL << c.luggage_size << COLOR_RESET << ", ";
	oss << COLOR_PROP << "safety" << COLOR_RESET << ": " << COLOR_VAL << c.safety << COLOR_RESET << ", ";
	oss << COLOR_PROP << "acceptability" << COLOR_RESET << ": " << COLOR_VAL << c.acceptability << COLOR_RESET;
	oss << '}';
	return oss;
}

namespace dr{

	// file-private
	namespace{
		std::string read_str(std::istringstream& iss){ 
			std::string data;
			std::getline(iss, data, ',');
			return data;
		}

		int read_int(std::istringstream& iss){ 
			return std::atoi(read_str(iss).c_str());
		}

		// parse line in a data set
		car parse_line(std::string& line){
			std::istringstream iss(line);

			car c{
				read_str(iss), // buying price
				read_str(iss), // maintenance price
				read_int(iss), // number of doors
				read_int(iss), // capacity
				read_str(iss), // luggage size
				read_str(iss), // safety
				read_str(iss), // acceptability
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

}
