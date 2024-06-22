#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

TEST_CASE("Пустой URL")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "";

	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL c IP адресом")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "https://192.168.1.1";
	Protocol expectedProtocol = Protocol::HTTPS;
	std::string expectedDomain = "192.168.1.1";
	short int expectedPort = 443;
	std::string expectedDocument = "";
	std::string expectedUrl = "https://192.168.1.1";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
	REQUIRE(url.GetURL() == expectedUrl);
}

TEST_CASE("URL c локальным доменным именем")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "http://localhost";
	Protocol expectedProtocol = Protocol::HTTP;
	std::string expectedDomain = "localhost";
	short int expectedPort = 80;
	std::string expectedDocument = "";
	std::string expectedUrl = "http://localhost";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
	REQUIRE(url.GetURL() == expectedUrl);
}

// hTtp://127.0.0.1:/aaaabc:

TEST_CASE("URL c разным регистром в протоколе")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "hTtpS://ya.ru";
	Protocol expectedProtocol = Protocol::HTTPS;
	std::string expectedDomain = "ya.ru";
	short int expectedPort = 443;
	std::string expectedDocument = "";
	std::string expectedUrl = "https://ya.ru";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
	REQUIRE(url.GetURL() == expectedUrl);
}

TEST_CASE("URL c документом")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "https://institute.ispringlearn.ru/courses?tab=to_do";
	Protocol expectedProtocol = Protocol::HTTPS;
	std::string expectedDomain = "institute.ispringlearn.ru";
	short int expectedPort = 443;
	std::string expectedDocument = "/courses?tab=to_do";
	std::string expectedUrl = "https://institute.ispringlearn.ru/courses?tab=to_do";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
	REQUIRE(url.GetURL() == expectedUrl);
}

TEST_CASE("URL с указанным стандартным портом одного протокола на другой протокол")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "https://ya.ru:80";
	Protocol expectedProtocol = Protocol::HTTPS;
	std::string expectedDomain = "ya.ru";
	short int expectedPort = 80;
	std::string expectedDocument = "";
	std::string expectedUrl = "https://ya.ru:80";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
	REQUIRE(url.GetURL() == expectedUrl);
}

TEST_CASE("URL с неверно указанным протоколом")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "httpс://ya.ru:80";

	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}


TEST_CASE("URL с неуказанным номером протокола после символа :")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:/abc";

	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL с отрицательным значением порта")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:-1";

	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL со значением порта 0")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:0";

	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL со значением порта, выходящим за верхний предел")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:65536";
	
	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

// проверять граничные условия (+)
TEST_CASE("URL со значением порта на границе верхнего предела")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:65535";
	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(false);
		return;
	}
	REQUIRE(true);
}

TEST_CASE("URL со значением порта на границе нижнего предела")
{
	setlocale(LC_ALL, "rus");
	std::string urlString = "http://ya.ru:1";
	try
	{
		CHttpUrl url(urlString);
	}
	catch (const CUrlParsingError&)
	{
		REQUIRE(false);
		return;
	}
	REQUIRE(true);
}
