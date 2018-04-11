#include <dirent.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef DATA_READER_H
#define DATA_READER_H

#define LETTER_COUNT 26
#define LETTER_OFFSET 97

struct lang_data{
	std::string lang;
	int letters[LETTER_COUNT]{0};
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

		lang_data cur_lang = {};
		cur_lang.lang = file->d_name;

		std::string subdir_name(dir_name);
		subdir_name.append("/").append(file->d_name).c_str();

		DIR* subdir = opendir(subdir_name.c_str());

		// loop training/<lang> directory
		while((file = readdir(subdir)) != NULL){
			if(file->d_name[0] == '.')
				continue;

			char c;
			std::string file_name = subdir_name.append("/").append(file->d_name);
			std::fstream fs(file_name, std::fstream::in);

			// read file char by char
			while(fs >> std::noskipws >> c){
				int index = c -LETTER_OFFSET;
				index = in_bounds(index, 0, LETTER_COUNT -1);

				if(index != -1)
					cur_lang.letters[index]++;
			}
		}
		closedir(subdir);
		data.push_back(cur_lang);
	}
	closedir(dir);
	return true;
}

std::string to_string(std::vector<lang_data>& data){
	std::ostringstream oss;
	auto end = data.end();
	for(auto it = data.begin(); it != end; it++){
		oss << it->lang << std::endl;
		for(int i = 0; i < LETTER_COUNT; i++)
			oss << '\t' << (char)(i +LETTER_OFFSET) << " - " << it->letters[i] << std::endl;
	}
	return oss.str();
}

} // end namespace

#endif // end include guard
