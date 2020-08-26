#include "utils.hpp"
#include <fstream>
#include <sstream>

std::string loadTextFile(const char* path){
	std::ifstream ifs(path);
	std::stringstream ss;
	std::string line;
	while(std::getline(ifs, line)){
		ss << line << "\n";
	}
	return ss.str();
}
