
#include "btle/exceptions/attribute_not_found.h"

using namespace btle::exceptions;

attribute_not_found::attribute_not_found(const std::string& what)
: std::runtime_error(what)
{
}

attribute_not_found::attribute_not_found()
: std::runtime_error("")
{
}

attribute_not_found::attribute_not_found(const attribute_not_found& other)
: std::runtime_error(std::string(other.what()))
{
}
