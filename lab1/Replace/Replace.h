#pragma once

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, std::string searchSubstr, std::string repalceSubstr);
void StreamProcessedLine(std::string line, std::ofstream& output, std::string searchSubstr, std::string replaceSubstr);
