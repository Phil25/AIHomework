#include <iostream>

class perc{
public:
	perc(const unsigned int num_of_coords, const double learning_param);
	~perc();

	bool get(const double* inputs);
	void tune(const double* inputs, bool actual, bool correct);

	double get_threshold();

	friend std::ostream& operator<<(std::ostream&, const perc&);

private:
	const unsigned int num_of_coords;
	double* weights;
	double threshold;
	double learning_param;

};
