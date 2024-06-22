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

// программа должна принимать домены без точек (+)
// программа должна принимать IP адреса (+)

bool CHttpUrl::ParseUrl(const std::string& url)
{
	const std::regex r(R"(([hH][tT][tT][pP][sS]?)://([^:^/]*)(:-?\d*)?(.*)?)");
	std::smatch m;
	std::regex_search(url, m, r);

	if (m.size())
	{
		m_protocol = CHttpUrl::ToLowerString(m[1].str()) == "http" ? Protocol::HTTP : Protocol::HTTPS;
		ParseDomainName(CHttpUrl::ToLowerString(m[2].str()));
		ParsePortValue(m[3].str());
		m_document = m[4].str();
		return true;
	}
	return false;
}

void CHttpUrl::ParseDomainName(const std::string &str)
{
	if (str.empty())
	{
		throw CUrlParsingError("Empty domain in url");
	}

	if (ParseDomain(str) || ParseLocal(str) || ParseIpv4(str))
	{
		m_domain = str;
	}
	else
	{
		throw CUrlParsingError("Invalid domain in url");
	}
}

bool CHttpUrl::ParseDomain(const std::string& str)
{
	const std::regex patternDomain("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");
	return regex_match(str, patternDomain);
}

bool CHttpUrl::ParseLocal(const std::string& str)
{
	const std::regex patternLocal("^(?!-)[A-Za-z0-9-]+$");
	return regex_match(str, patternLocal);
}

bool CHttpUrl::ParseIpv4(const std::string& str)
{
	const std::regex patternIpv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
	return regex_match(str, patternIpv4);
}

void CHttpUrl::ParsePortValue(const std::string& rawPortData)
{
	if (rawPortData.length() == 1)
	{
		throw CUrlParsingError("Port value not fount after port prefix");
	}
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
	ParseDomain(domain);
	m_document = document;
	m_port = protocol == Protocol::HTTP ? 80 : 443;
	SetUrl();
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port) :
	m_protocol(protocol)
{
	ParseDomain(domain);
	m_document = document;
	if (port < 1 || port > 65535)
	{
		throw CUrlParsingError("Used invalid port value");
	}
	m_port = port;

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
	if ((m_port != 80 && m_port != 443) || (m_port == 80 && m_protocol == Protocol::HTTPS) || (m_port == 443 && m_protocol == Protocol::HTTP))
	{
		m_url += ":";
		m_url += std::to_string(m_port);
	}
	m_url += m_document;
}
