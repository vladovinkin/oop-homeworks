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

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
}

TEST_CASE("URL c локальным доменным именем")
{
	setlocale(LC_ALL, "rus");

	std::string urlString = "http://localhost";
	Protocol expectedProtocol = Protocol::HTTP;
	std::string expectedDomain = "localhost";
	short int expectedPort = 80;
	std::string expectedDocument = "";

	CHttpUrl url(urlString);

	REQUIRE(url.GetProtocol() == expectedProtocol);
	REQUIRE(url.GetDomain() == expectedDomain);
	REQUIRE(url.GetPort() == expectedPort);
	REQUIRE(url.GetDocument() == expectedDocument);
}
