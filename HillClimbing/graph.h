#ifndef GRAPH_H
#define GRAPH_H


#include <vector>
#include <ostream>
#include <iostream>

class graph{
	int size;
	std::vector<std::vector<int>> data;
	int last[2]{0, 0};

public:
	graph(int size):
		size(size),
		data(size, std::vector<int>(size))
	{}

	void add_col(int value){
		data[last[0]][last[1]++] = value;
	}

	void add_row(){
		last[0]++;
		last[1] = 0;
	}

	const int& operator()(int v1, int v2) const{
		return data[v1][v2];
	}

	friend std::ostream& operator<<(std::ostream&, const graph&);
};

std::ostream& operator<<(std::ostream& os, const graph& g){
	for(int row = 0; row < g.size; row++){
		for(int col = 0; col < g.size; col++)
			os << g.data[row][col] << ' ';
		os << std::endl;
	}
	return os;
}


#endif
