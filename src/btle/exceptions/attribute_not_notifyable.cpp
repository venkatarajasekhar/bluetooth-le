
#include "btle/exceptions/attribute_not_notifyable.h"

using namespace btle::exceptions;

attribute_not_notifyable::attribute_not_notifyable(const std::string& what)
: std::runtime_error(what)
{
}

attribute_not_notifyable::attribute_not_notifyable()
: std::runtime_error("")
{
}

attribute_not_notifyable::attribute_not_notifyable(const attribute_not_notifyable& other)
: std::runtime_error(std::string(other.what()))
{
}


