#include <Windows.h>
#include <iostream>
#include <sstream>
#include <optional>
#include <map>

typedef std::map<std::string, std::string> DictMap;

struct Args {
	std::string fileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Invert.exe <source file>\n";
		return std::nullopt;
	}
	Args args;
	args.fileName = argv[1];
	return args;
}


DictMap CreateDict(int argc, char* argv[])
{
	DictMap dict;

	if (argc > 2)
	{
		throw std::exception("Неверное количество аргументов.\n\nИспользование программы: dict.exe <dict_file>\n");
	}

	if (argc == 2)
	{
		//std::string fileName = argv[1];

		// чтение словаря из файла
		// при чтении перевести слова-источники в нижний регистр 
		/*
			std::string ToLowerString(const std::string& s)
			{
				std::string out = "";
				for (auto i = 0; i < s.length(); i++)
				{
					out += std::tolower(s[i]);
				}
				return out;
			}
		*/
		dict["cat"] = "кошка";
		dict["dog"] = "собака";
		dict["table"] = "стол";
	}

	return dict;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	DictMap dict;
	
	try
	{
		dict = CreateDict(argc, argv);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}

	if (dict.size() > 0)
	{
		std::string line, trans;

		for(;;)
		{
			std::cout << ">";
			std::getline(std::cin, line);
			if (line == "...")
			{
				break;
			}

			if (dict.contains(line))
			{
				std::cout << dict[line] << '\n';
			}
			else
			{
				std::cout << "Неизвестное слово “" << line << "”. Введите перевод или пустую строку для отказа.\n>";
				std::getline(std::cin, trans);
				if (trans.length() > 0)
				{
					dict[line] = trans;
					std::cout << "Слово “" << line << "” сохранено в словаре как “" << trans << "”.\n";
				}
				else
				{
					std::cout << "Слово “" << line << "” проигнорировано.\n";
				}
			}
		}

		// проанализировать, были ли добавлены новые слова в словарь - 
		//	если добавлены - спросить о сохранении (В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.)
		//		если да - сохранить (Изменения сохранены. ), если нет, то сообщение (Вы отказались от сохранения обновлений. )
		// (До свидания.)

		for (auto iter{ dict.cbegin() }; iter != dict.cend(); iter++)
		{
			std::cout << iter->first << "\t" << iter->second << std::endl;
		}
	}

	return 0;
}
