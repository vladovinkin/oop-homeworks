// Replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Replace.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, std::string searchSubstr, std::string replaceSubstr)
{
	while (!input.eof())
	{
		std::string line;
		std::getline(input, line);

		// Заменяем подстроки заданной строки на значение строки поиска и записываем результат в выходной файл
		StreamProcessedLine(line, output, searchSubstr, replaceSubstr);
	}
}

void StreamProcessedLine(std::string line, std::ofstream& output, std::string searchSubstr, std::string replaceSubstr)
{
	std::size_t foundPos = 0, curPos = 0;

	foundPos = line.find(searchSubstr);
	if (replaceSubstr.length() && foundPos != std::string::npos)
	{
		do
		{
			std::cout << line.substr(curPos, foundPos - curPos) << replaceSubstr;
			curPos = foundPos + searchSubstr.length();
			foundPos = line.find(searchSubstr, curPos);
		} while (foundPos != std::string::npos);
		std::cout << line.substr(curPos) << "\n";
	}
	else
	{
		std::cout << line << "\n";
	}
}

int main(int argc, char* argv[])
{
	// Проверка правильности аргументов командной строки
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	// Открываем входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	// Открываем выходной файл
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}

	// Заменяем подстроки входного файла на значение строки поиска и записываем результат в выходной файл
	CopyStreamWithReplace(input, output, args->searchString, args->replaceString);

	// Проверяем случилась ли проблема чтения входного файла
	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";

		return 1;
	} 

	// Проверяем на ошибку записи в выходной файл
	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}
