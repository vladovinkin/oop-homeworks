#pragma once
#include <string>

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, std::string searchSubstr, std::string repalceSubstr);
void StreamProcessedLine(std::string line, std::ofstream& output, std::string searchSubstr, std::string replaceSubstr);
std::string GetOneLineReplaced(std::string line, std::string searchSubstr, std::string replaceSubstr);