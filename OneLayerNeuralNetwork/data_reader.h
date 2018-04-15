#include <dirent.h>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef DATA_READER_H
#define DATA_READER_H

#define LETTER_COUNT 26
#define LETTER_OFFSET 97

struct lang_data{
	std::string lang;
	std::vector<std::array<int, LETTER_COUNT>> letters;
};

namespace dr{

int in_bounds(int x, int lower, int upper){
	return (lower <= x && x <= upper) ? x : -1;
}

bool get_lang_data(const char* dir_name, std::vector<lang_data>& data){
	struct dirent* file;
	DIR* dir = opendir(dir_name);
	if(dir == NULL)
		return false;

	// loop training directory
	while((file = readdir(dir)) != NULL){
		if(file->d_name[0] == '.')
			continue;

		lang_data cur_lang{};
		cur_lang.lang = file->d_name;

		std::string subdir_name(dir_name);
		subdir_name.append("/").append(file->d_name);

		DIR* subdir = opendir(subdir_name.c_str());

		// loop training/<lang> directory
		while((file = readdir(subdir)) != NULL){
			if(file->d_name[0] == '.')
				continue;

			std::string file_name(subdir_name); 
			file_name.append("/").append(file->d_name);

			char c;
			std::array <int, LETTER_COUNT> cur_letters{0};
			std::fstream fs(file_name, std::fstream::in);

			// read file char by char
			while(fs >> std::noskipws >> c){
				int index = std::tolower(c) -LETTER_OFFSET;
				index = in_bounds(index, 0, LETTER_COUNT -1);

				if(index != -1)
					cur_letters[index]++;
			}

			cur_lang.letters.push_back(cur_letters);
		}
		closedir(subdir);
		data.push_back(cur_lang);
	}
	closedir(dir);
	return true;
}

std::string to_string(std::vector<lang_data>& data){
	//return "";
	std::ostringstream oss;
	auto end = data.end();
	// iterate languages
	for(auto it = data.begin(); it != end; it++){
		oss << it->lang << std::endl;
		
		// iterate letter vectors
		auto letend = it->letters.end();
		for(auto letit = it->letters.begin(); letit != letend; letit++){

			oss << "\tFile" << std::endl;
			// iterate actual letters
			for(int i = 0; i < LETTER_COUNT; i++)
				oss << "\t\t" << (char)(i +LETTER_OFFSET) << " - " << (*letit)[i] << std::endl;
		}
	}
	return oss.str();
}

} // end namespace

#endif // end include guard
