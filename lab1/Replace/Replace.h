#pragma once
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, std::string searchSubstr, std::string repalceSubstr);
std::string GetOneLineReplaced(std::string line, std::string searchSubstr, std::string replaceSubstr);