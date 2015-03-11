
#include "btle/exceptions/not_implemented.h"

using namespace btle::exceptions;

not_implemented::not_implemented(const std::string& what)
: std::runtime_error(what)
{
}

not_implemented::not_implemented()
: std::runtime_error("")
{
}

not_implemented::not_implemented(const not_implemented& other)
: std::runtime_error(std::string(other.what()))
{
}





