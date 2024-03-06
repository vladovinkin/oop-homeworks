// Replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Replace.h"
#include <fstream>
#include <iostream>

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

void CopyFileWithReplace(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchSubstr, const std::string& replaceSubstr)
{
	// Открываем входной файл
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open '" + inputFileName + "' for reading");
	}

	// Открываем выходной файл
	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open '" + outputFileName + "' for writing");
	}

	// Заменяем подстроки входного файла на значение строки поиска и записываем результат в выходной файл
	CopyStreamWithReplace(input, output, searchSubstr, replaceSubstr);

	// Проверяем на ошибку записи в выходной файл
	if (!output.flush())
	{
		throw std::runtime_error("Failed to write data to output file '" + outputFileName + "'");
	}
}

void CopyStreamWithReplace(std::ifstream& input, std::ofstream& output, const std::string& searchSubstr, const std::string& replaceSubstr)
{
	std::string line;

	// этот цикл будет выполняться бесконечно если произойдёт ошибка
	while (!input.eof())
	{
		std::getline(input, line);

		// Проверяем случилась ли проблема чтения входного файла
		if (input.bad())
		{
			throw std::runtime_error("Failed to read data from input file");
		}

		// Заменяем подстроки очередной строки на значение строки поиска и записываем результат в выходной файл
		output << GetOneLineReplaced(line, searchSubstr, replaceSubstr) << (!input.eof() ? "\n" : "");
	}
}

// find 1 time, append <= 2
std::string GetOneLineReplaced(const std::string& line, const std::string& searchSubstr, const std::string& replaceSubstr)
{
	std::string resultLine;
	std::size_t foundPos = 0, curPos = 0;

	if (!searchSubstr.empty())
	{
		while (foundPos != std::string::npos)
		{
			foundPos = line.find(searchSubstr, curPos);
			if (foundPos != std::string::npos)
			{
				resultLine.append(line, curPos, foundPos - curPos);
				resultLine.append(replaceSubstr);
				curPos = foundPos + searchSubstr.length();
			}
			else
			{
				resultLine.append(line, curPos);
				return resultLine;
			}
		}
	}
	return line;
}

int main(int argc, char* argv[])
{
	// Проверка правильности аргументов командной строки
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	try
	{
		CopyFileWithReplace(args->inputFileName, args->outputFileName, args->searchString, args->replaceString);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}

	return 0;
}
