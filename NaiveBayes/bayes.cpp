#include <iostream>
#include <map>

#include "data_reader.h"
#include "fraction.h"

#define iterate(it, data) \
	for(auto it = data.begin(); it != data.end(); it++)

std::string bayes(const car& c, std::vector<car>& data){
	std::cout << "Input:" << std::endl;
	std::cout << c << std::endl;
	// a priori probability of each output
	std::map<std::string, fraction> out_prob;

	iterate(it, car::attrib_sets[ACCEPTABILITY]){
		fraction frac;
		frac.nominator = car::amount[ACCEPTABILITY][*it];
		frac.denominator = data.size();
		frac.smooth(1, car::unique[ACCEPTABILITY]);

		out_prob.insert(std::make_pair(*it, frac));
	}

	iterate(decision, out_prob){
		// all data rows filtered for output
		std::vector<car> data_of_output(car::amount[ACCEPTABILITY][decision->first]);
		iterate(it, data)
			if(it->attribs[ACCEPTABILITY].compare(decision->first) == 0)
				data_of_output.push_back(*it);

		for(int i = 0; i < ATTRIB_COUNT -1; i++){ // -1 to exclude decision attribute
			fraction frac;
			// count how many filtered examples have the attribute of same value
			iterate(it, data_of_output)
				if(it->attribs[i].compare(c.attribs[i]) == 0)
					frac.nominator++;
			frac.denominator = data_of_output.size();
			frac.smooth(1, car::unique[i]);

			out_prob[decision->first] *= frac;
		}
	}

	std::string max_key = out_prob.begin()->first;
	fraction max_val = out_prob.begin()->second;

	iterate(it, out_prob){
		std::cout << it->first << ": " << it->second << std::endl;
		if(it->second.result() <= max_val.result())
			continue;
		max_key = it->first;
		max_val = it->second;
	}

	return max_key;
}

void run_test(std::vector<car>& test_data, std::vector<car>& training_data){
	float all = 0, correct = 0;

	auto end = test_data.end();
	for(auto it = test_data.begin(); it != end; it++){
		std::string guess = bayes(*it, training_data);
		correct += guess.compare(it->attribs[ACCEPTABILITY]) == 0;
		all++;
	}

	std::cout << "Accuracy: " << correct /all *100 << '%' << std::endl;
}

int main(){

	// vectors storing train and test data
	std::vector<car> test_data;
	std::vector<car> training_data;

	// parse assignment files
	dr::read_data("test", test_data);
	dr::read_data("training", training_data);
	dr::calc_unique_values(training_data);

	// run the algorithm for the test data
	run_test(test_data, training_data);

	iterate(it, test_data)
		std::cout << *it << std::endl;

	return 0;
}
