#pragma once
#include "CUrlParsingError.h"
#include <cctype>

enum class Protocol
{
    HTTP,
    HTTPS
};

// TODO: выучить гарантии безопасности исключений и их отличия

class CHttpUrl
{
public:
    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в эту строку
    // не должен включаться
    std::string GetURL()const;

    // возвращает доменное имя
    std::string GetDomain()const;

    /*
        Возвращает имя документа. Примеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // возвращает тип протокола
    Protocol GetProtocol()const;

    // возвращает номер порта
    unsigned short GetPort()const;

    // переводит строку в нижний регистр
    static std::string ToLowerString(const std::string& s)
    {
        std::string out = "";
        for (auto i = 0; i < s.length(); i++)
        {
            out += std::tolower(s[i]);
        }
        return out;
    }

    // получает данные порта из сырых данных парсинга
    void ParsePortValue(const std::string& rawPortData);

    // валидация и присвоение доменного имени
    void ParseDomainName(const std::string &str);
    bool ParseDomain(const std::string& str);
    bool ParseLocal(const std::string& str);
    bool ParseIpv4(const std::string& str);
private:
    void SetUrl();
    bool ParseUrl(const std::string&);
    std::string m_url;
    std::string m_domain;
    std::string m_document;
    unsigned short m_port;
    Protocol m_protocol;
};

