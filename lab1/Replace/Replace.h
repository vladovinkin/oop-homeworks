#pragma once
#include <string>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

void CopyFileWithReplace(const std::optional<Args>& args);
void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, const std::string &searchSubstr, const std::string &repalceSubstr);
std::string GetOneLineReplaced(const std::string &line, const std::string &searchSubstr, const std::string &replaceSubstr);