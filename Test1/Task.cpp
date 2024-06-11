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

	int line_num = 0;
	for (const Code& code : codes) {
		std::string line = code.description;
		std::replace(line.begin(), line.end(), ' ', '_');

		ostream << '\n' << line << ' ' << code.done;
		line_num++;
	}

	//TODO: Parser Function (can do all in the same for loop above):
	//needs to save per line of code, what operations are used and add them using "ostream <<..."
	//we already have the code, and the line number, so all of the necessary things are there
	//just need to save all of it into a text file

	//NOTES (for me):
	//so basically everytime the user inputs a line (in our case or world) a list will be sent to Koko's function and checked for any anomalies
	//but for now, all lists will be saved into a text file.
	//as for checking for any anomalies, we will NOT be doing that nor outputting any outputs!
	//too much work and I don't think it can be done in this short time!
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
