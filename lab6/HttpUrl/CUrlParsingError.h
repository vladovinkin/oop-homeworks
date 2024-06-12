#pragma once
#include <stdexcept>

enum class Protocol
{
    HTTP,
    HTTPS
};

class CUrlParsingError : public std::invalid_argument
{
public:
   // …
};

