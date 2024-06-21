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

void OutputUrlResult(const CHttpUrl &httpUrl, IO io)
{
	io.output << "------- result start -------\n";
	io.output << "protocol: HTTP" << (httpUrl.GetProtocol() == Protocol::HTTPS ? "S\n" : "\n");
	io.output << "domain: " << httpUrl.GetDomain() << "\n";
	io.output << "port: " << httpUrl.GetPort() << "\n";
	io.output << "document: " << httpUrl.GetDocument() << "\n";
	io.output << "Stored URL: " << httpUrl.GetURL() << "\n";
	io.output << "------- result end -------\n\n";
}

void ParseUrlAndOutputResult(IO io)
{ 
	std::string in;
	while (std::getline(io.input, in))
	{
		try
		{
			CHttpUrl httpUrl = CHttpUrl(in);
			OutputUrlResult(httpUrl, io);
		} 
		// выяснить подробности про срезку
		catch (CUrlParsingError& e)
		{
			std::cout << e.what() << "\n";
		}
		std::cout << "\n";
		// std::nested_exception - ?
	}
}

int main() {
	ParseUrlAndOutputResult({ std::cin, std::cout });
	return 0;
}
