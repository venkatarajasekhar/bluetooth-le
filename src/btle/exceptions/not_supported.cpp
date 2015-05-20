#include "btle/exceptions/not_supported.h"

using namespace btle::exceptions;

not_supported::not_supported(const std::string& what)
: std::runtime_error(what)
{
}

not_supported::not_supported()
: std::runtime_error("")
{
}

not_supported::not_supported(const not_supported& other)
: std::runtime_error(std::string(other.what()))
{
}


