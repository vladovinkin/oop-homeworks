#pragma once
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
    using invalid_argument::invalid_argument;
   // explicit CUrlParsingError(char* msg);
};
