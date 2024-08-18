#pragma once
#include <string>
#include <vector>

/*struct Code
{
	std::string description;
	//bool done;
};*/

void saveCodeToFile(const std::string& code, const std::string& fileName, const std::string& fileName2, const std::string& fileName3);
std::string loadCodeFromFile(const std::string& fileName, const std::string& fileName2);
