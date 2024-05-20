#pragma once
#include <string>
#include <vector>

struct Code
{
	std::string code_line;
};

void saveCodeToFile(const std::vector<Code>& codes, const std::string& fileName);
std::vector<Code> loadCodeFromFile(const std::string& fileName);
