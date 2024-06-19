#include "stdafx.h"
#include "CHttpUrl.h"
#include <iostream>
#include <vector>
#include <regex>

struct IO
{
	std::istream& input;
	std::ostream& output;
};

void ParseUrlAndOutputResult(IO io)
{ 
	std::string in;
	while (std::getline(io.input, in))
	{
		try
		{
			CHttpUrl httpUrl = CHttpUrl(in);
			io.output << httpUrl.GetURL() << "\n";
		} // выяснить подробности про срезку
		catch (CUrlParsingError& e)
		{
			std::cout << e.what() << "\n";
		}
		// std::nested_exception - ?
	}
}

int main() {
	ParseUrlAndOutputResult({ std::cin, std::cout });

	return 0;
}
