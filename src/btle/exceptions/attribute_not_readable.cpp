
#include "btle/exceptions/attribute_not_readable.h"

using namespace btle::exceptions;

attribute_not_readable::attribute_not_readable(const std::string& what)
: std::runtime_error(what)
{
}

attribute_not_readable::attribute_not_readable()
: std::runtime_error("")
{
}

attribute_not_readable::attribute_not_readable(const attribute_not_readable& other)
: std::runtime_error(std::string(other.what()))
{
}

