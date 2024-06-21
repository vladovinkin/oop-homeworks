#include "stdafx.h"
#include "CHttpUrl.h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	if (ParseUrl(url))
	{
		SetUrl();
	}
	else
	{
		throw CUrlParsingError("Url is not valid");
	}
}

bool CHttpUrl::ParseUrl(const std::string& url)
{
	const std::regex r(R"(([hH][tT][tT][pP][sS]?)://([^:^/]*)(:-?\d*)?(.*)?)");
	std::smatch m;
	std::regex_search(url, m, r);

	if (m.size())
	{
		m_protocol = CHttpUrl::ToLowerString(m[1].str()) == "http" ? Protocol::HTTP : Protocol::HTTPS;
		ParseDomain(CHttpUrl::ToLowerString(m[2].str()));
		ParsePortValue(m[3].str());
		m_document = m[4].str();
		return true;
	}
	return false;
}

void CHttpUrl::ParseDomain(const std::string &str)
{
	// Regex to check valid domain name.
	const std::regex pattern("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");

	if (str.empty())
	{
		throw CUrlParsingError("Empty domain in url");
	}

	if (regex_match(str, pattern))
	{
		m_domain = str;
	}
	else
	{
		throw CUrlParsingError("Invalid domain in url");
	}
}

void CHttpUrl::ParsePortValue(const std::string& rawPortData)
{
	std::string portString = rawPortData.empty() ? "" : rawPortData.substr(1);
	if (portString.empty())
	{
		m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
	}
	else
	{
		int portInt = std::atoi(portString.c_str());
		if (portInt < 1 || portInt > 65535)
		{
			throw CUrlParsingError("Used invalid port value");
		}
		m_port = static_cast<unsigned short>(portInt);
	}
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
	if (m_port != 80 && m_port != 443)
	{
		m_url += ":";
		m_url += (unsigned)m_port;

	}
	m_url += m_document;
}
