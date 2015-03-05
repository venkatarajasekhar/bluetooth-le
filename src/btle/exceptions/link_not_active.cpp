
#include "btle/exceptions/link_not_active.h"

using namespace btle::exceptions;

link_not_active::link_not_active(const std::string& what)
: std::runtime_error(what)
{
}

link_not_active::link_not_active()
: std::runtime_error("")
{
}

link_not_active::link_not_active(const link_not_active& other)
: std::runtime_error(std::string(other.what()))
{
}



