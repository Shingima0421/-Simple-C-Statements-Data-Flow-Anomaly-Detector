#pragma once
#include <string>
#include <vector>

struct Code
{
	std::string description;
	bool done;
};

void saveCodeToFile(const std::vector<Code>& codes, const std::string& fileName, const std::string& fileName2);
std::vector<Code> loadCodeFromFile(const std::string& fileName);
