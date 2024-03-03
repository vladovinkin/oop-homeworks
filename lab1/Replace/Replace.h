#pragma once
#include <string>

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, std::string searchSubstr, std::string repalceSubstr);
std::string GetOneLineReplaced(std::string line, std::string searchSubstr, std::string replaceSubstr);