
#include "btle/exceptions/service_not_found.h"

using namespace btle::exceptions;

service_not_found::service_not_found(const std::string& what)
: std::runtime_error(what)
{
}

service_not_found::service_not_found()
: std::runtime_error("")
{
}

service_not_found::service_not_found(const service_not_found& other)
: std::runtime_error(std::string(other.what()))
{
}




