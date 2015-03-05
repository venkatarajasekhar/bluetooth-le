
#include "btle/exceptions/attribute_not_writable.h"

using namespace btle::exceptions;

attribute_not_writable::attribute_not_writable(const std::string& what)
: std::runtime_error(what)
{
}

attribute_not_writable::attribute_not_writable()
: std::runtime_error("")
{
}

attribute_not_writable::attribute_not_writable(const attribute_not_writable& other)
: std::runtime_error(std::string(other.what()))
{
}


