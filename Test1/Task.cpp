#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveCodeToFile(const std::vector<Code>& codes, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << codes.size();

	for (const Code& code : codes) {
		std::string line = code.code_line;
		std::replace(line.begin(), line.end(), ' ', '_');

		ostream << '\n' << line;
	}
}

std::vector<Code> loadCodeFromFile(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<Code>();
	}

	std::vector<Code> codes;
	std::ifstream istream(fileName);

	int n;
	istream >> n;

	for (int i = 0; i < n; i++) {
		std::string code_line;

		istream >> code_line;
		std::replace(code_line.begin(), code_line.end(), '_', ' ');
		codes.push_back(Code{ code_line });
	}

	return codes;
}
