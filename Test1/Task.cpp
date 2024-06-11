#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveCodeToFile(const std::vector<Code>& codes, const std::string& fileName, const std::string& fileName2)
{
	std::ofstream ostream(fileName);
	ostream << codes.size();

	std::ofstream ostream2(fileName2);
	ostream2 << codes.size();

	for (const Code& code : codes) {
		std::string line = code.description;
		std::replace(line.begin(), line.end(), ' ', '_');

		ostream << '\n' << line << ' ' << code.done;
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
		std::string description;
		bool done;

		istream >> description >> done;
		std::replace(description.begin(), description.end(), '_', ' ');
		codes.push_back(Code{ description, done });
	}

	return codes;
}
