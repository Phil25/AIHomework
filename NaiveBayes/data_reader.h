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

	// number of unique values for each attribute
	static int7 unique;
	friend std::ostream& operator<<(std::ostream&, const car&);

};

int7 car::unique{0};

// hidden cout wrappers
namespace{
	void print_line(std::ostream& oss, std::string property, std::string value, std::string end){
		oss << COLOR_PROP << property << COLOR_RESET << ": " << COLOR_VAL << value << COLOR_RESET << end;
	}

	void print_line(std::ostream& oss, std::string property, int value, std::string end){
		oss << COLOR_PROP << property << COLOR_RESET << ": " << COLOR_VAL << value << COLOR_RESET << end;
	}
}

std::ostream& operator<<(std::ostream& oss, const car& c){
	oss << '{';
	print_line(oss, "b. price", c.buying_price, ", ");
	print_line(oss, "m. price", c.maintenance_price, ", ");
	print_line(oss, "door num", c.door_num, ", ");
	print_line(oss, "capacity", c.capacity, ", ");
	print_line(oss, "luggage", c.luggage_size, ", ");
	print_line(oss, "safety", c.safety, ", ");
	print_line(oss, "acceptability", c.acceptability, "");
	oss << '}';
	return oss;
}

namespace dr{

	// hidden readers
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

	// I am aware this function is an ugly mess
	void calc_unique_values(std::vector<car>& data){

		// sets for each attribute
		std::set<std::string> buying_prices;
		std::set<std::string> maintenance_prices;
		std::set<int> door_nums;
		std::set<int> capacities;
		std::set<std::string> luggage_sizes;
		std::set<std::string> safeties;

		// fill the sets
		auto end = data.end();
		for(auto it = data.begin(); it != end; it++){
			buying_prices.insert(it->buying_price);
			maintenance_prices.insert(it->maintenance_price);
			door_nums.insert(it->door_num);
			capacities.insert(it->capacity);
			luggage_sizes.insert(it->luggage_size);
			safeties.insert(it->safety);
		}

		// get the unique values
		car::unique[0] = buying_prices.size();
		car::unique[1] = maintenance_prices.size();
		car::unique[2] = door_nums.size();
		car::unique[3] = capacities.size();
		car::unique[4] = luggage_sizes.size();
		car::unique[5] = safeties.size();
	}

}
