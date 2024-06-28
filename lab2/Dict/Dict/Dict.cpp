#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

typedef std::map<std::string, std::string> DictMap;

struct Dict
{
	DictMap dict;
	std::string fileName;
	bool isMod;
};

std::string ToLowerString(const std::string& s)
{
	std::string out = "";
	for (auto i = 0; i < s.length(); i++)
	{
		out += std::tolower(s[i]);
	}
	return out;
}

bool IsKeyPressedYes()
{
	char key;
	do
	{
		key = _getch();
	} 
	while (!key);

	return (key == 'Y' || key == 'y');
}

Dict CreateDict(int argc, char* argv[])
{
	Dict dict{ {}, "", false};

	if (argc > 2)
	{
		std::cout << "Неверное количество аругментов\n";
		std::cout << "Использование: Dict.exe <dict_file>\n";
	} 
	else if (argc == 2)
	{
		std::string fileName = argv[1];
		std::ifstream file;

		file.open(fileName);
		if (!file.is_open())
		{
			throw std::runtime_error("Ошибка. Не могу открыть файл '" + fileName + "' для чтения.");
		}

		std::string line, src = "";
		while (std::getline(file, line) && line.length() > 0)
		{
			if (src.length() == 0)
			{
				src = line;
			}
			else
			{
				dict.dict[ToLowerString(src)] = line;
				src.clear();
			}
		}
		if (src.length() != 0)
		{
			throw std::runtime_error("Ошибка. В файле '" + fileName + "' для какого-то слова нет перевода.");
		}
		dict.fileName = fileName;
	}

	return dict;
}

void CheckDictChangesAndSaveIfNeed(Dict& dict)
{
	if (dict.isMod)
	{
		std::cout << "В словарь были внесены изменения. Нажмите Y или y для сохранения перед выходом.\n";
		if (IsKeyPressedYes())
		{
			SaveDict(dict);
			std::cout << "Изменения сохранены. ";
		}
		else
		{
			std::cout << "Вы отказались от сохранения обновлений. ";
		}
	}
	std::cout << "До свидания.\n";
}

void InteractWithDict(Dict& dict)
{
	std::string line, trans;

	for (;;)
	{
		std::cout << ">";
		std::getline(std::cin, line);
		if (line == "...")
		{
			break;
		}
		std::string lowSrc = ToLowerString(line);
		if (dict.dict.contains(lowSrc))
		{
			std::cout << dict.dict[lowSrc] << '\n';
		}
		else
		{
			std::cout << "Неизвестное слово “" << line << "”. Введите перевод или пустую строку для отказа.\n>";
			std::getline(std::cin, trans);
			if (trans.length() > 0)
			{
				dict.dict[line] = trans;
				std::cout << "Слово “" << line << "” сохранено в словаре как “" << trans << "”.\n";
				dict.isMod = true;
			}
			else
			{
				std::cout << "Слово “" << line << "” проигнорировано.\n";
			}
		}
	}

	CheckDictChangesAndSaveIfNeed(dict);
}

void SaveDict(Dict dict)
{
	std::ofstream file;
	file.open(dict.fileName);
	for (auto iter{ dict.dict.cbegin() }; iter != dict.dict.cend(); iter++)
	{
		file << iter->first << "\n" << iter->second << '\n';
	}
	file.close();
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Dict dict;

	try
	{
		dict = CreateDict(argc, argv);
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}

	if (dict.dict.size() > 0)
	{
		InteractWithDict(dict);
	}

	return 0;
}
