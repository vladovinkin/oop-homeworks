#include "stdafx.h"
#include "CHttpUrl.h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string inLow = CHttpUrl::ToLowerString(url);
	if (ParseUrl(inLow))
	{
		SetUrl();
	}
	else
	{
		throw CUrlParsingError("Url not valid");
	}
}

bool CHttpUrl::ParseUrl(const std::string& url)
{
	const std::regex r(R"((https?)://([^:^/]*)(:\d*)?(.*)?)");
	std::smatch m;
	std::regex_search(url, m, r);

	if (m.size())
	{
		m_protocol = m[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		m_domain = m[2].str();
		m_port = m[3].str().length() 
			? (unsigned short)std::stoul(m[4].str())
			: 0;
		m_document = m[4].str();
		return true;
	}
	return false;
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol) :
		m_protocol(protocol)
{
	// проверить все составляющие на корректность
	// занести в поля
	// значение порта выставить в соответствие с протоколом

	SetUrl();
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port) :
	m_protocol(protocol)
{
	// проверить все составляющие на корректность
	// занести в поля

	SetUrl();
}

std::string CHttpUrl::GetURL()const
{
	return m_url;
}

std::string CHttpUrl::GetDomain()const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument()const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol()const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort()const
{
	return m_port;
}

void CHttpUrl::SetUrl()
{
	// на основе полей сгенерировать значение URL и присвоить полю
	m_url = "";
	m_url += m_protocol == Protocol::HTTP ? "http" : "https";
	m_url += "://" + m_domain;
	/*if (m_port)
	{
		m_url += ":";
		m_url += (unsigned)m_port;

	}*/
	m_url += m_document;
}
