#include <iostream>
#include <map>

#include "data_reader.h"
#include "fraction.h"

void filter_by_output(const std::vector<car>& from, const std::string& decision, std::vector<car>& to){
	for(auto c : from)
		if(c.attribs[ACCEPTABILITY].compare(decision) == 0)
			to.push_back(c);
}

int count_appearances(const std::string& attrib_name, const std::vector<car>& data, int pos){
	int count = 0;
	for(auto c : data)
		count += attrib_name.compare(c.attribs[pos]) == 0;
	return count;
}

std::string max(std::map<std::string, fraction>& m){
	std::string max_key = m.begin()->first;
	fraction max_val = m.begin()->second;

	for(auto p : m){
		if(p.second <= max_val)
			continue;
		max_key = p.first;
		max_val = p.second;
	}

	return max_key;
}

std::string bayes(const car& c, std::vector<car>& data){
	std::cout << "Input:" << std::endl;
	std::cout << c << std::endl;

	// a priori probability of each output
	std::map<std::string, fraction> out_prob;

	for(auto attrib_name : car::attrib_sets[ACCEPTABILITY]){
		fraction decision_frac;
		decision_frac.nominator = car::amount[ACCEPTABILITY][attrib_name];
		decision_frac.denominator = data.size();
		decision_frac.smooth(1, car::unique[ACCEPTABILITY]);
		std::cout << std::endl << dr::format_prob(car::attribs_cols[ACCEPTABILITY], attrib_name, decision_frac) << std::endl;

		// all data rows filtered for output
		std::vector<car> data_of_output(car::amount[ACCEPTABILITY][attrib_name]);
		filter_by_output(data, attrib_name, data_of_output);

		// iterate every attribute excluding decision
		for(int i = 0; i < ATTRIB_COUNT -1; i++){
			fraction frac;
			frac.nominator = count_appearances(c.attribs[i], data_of_output, i);
			frac.denominator = count_appearances(attrib_name, data_of_output, ACCEPTABILITY);
			frac.smooth(1, car::unique[i]);
			std::cout << dr::format_prob(car::attribs_cols[i], c.attribs[i], car::attribs_cols[ACCEPTABILITY], attrib_name, frac) << std::endl;
			decision_frac *= frac;
		}

		out_prob.insert(std::make_pair(attrib_name, decision_frac));
		std::cout << dr::format_prob(car::attribs_cols[ACCEPTABILITY], attrib_name, "X", "(..)", decision_frac) << std::endl;

	}

	std::string guess = max(out_prob);
	std::cout << std::endl << "Guess: " << guess << std::endl << std::endl;
	std::cout << "=====================================" << std::endl;

	return guess;
}

void run_test(std::vector<car>& test_data, std::vector<car>& training_data){
	float all = 0, correct = 0;

	auto end = test_data.end();
	for(auto it = test_data.begin(); it != end; it++){
		std::string guess = bayes(*it, training_data);
		correct += guess.compare(it->attribs[ACCEPTABILITY]) == 0;
		all++;
		//break;
	}

	std::cout << "Accuracy: " << correct /all *100 << '%' << std::endl;
}

void input_loop(std::vector<car>&);

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

	while(1)
		input_loop(training_data);

	return 0;
}

void input_loop(std::vector<car>& data){
	std::cout << std::endl;
	car c;
	for(int i = 0; i < ATTRIB_COUNT -1; i++){
		std::cout << COLOR_PROP << car::attribs_cols[i] << COLOR_RESET << " [/";
		for(std::string attrib : car::attrib_sets[i])
			std::cout << COLOR_VAL << attrib << COLOR_RESET << '/';
		std::cout << "]: ";
		std::getline(std::cin, c.attribs[i]);
	}
	c.attribs[ACCEPTABILITY] = bayes(c, data);
}
