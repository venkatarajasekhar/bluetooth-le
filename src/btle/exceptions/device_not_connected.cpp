
#include "btle/exceptions/device_not_connected.h"

using namespace btle::exceptions;

device_not_connected::device_not_connected(const std::string& what)
: std::runtime_error(what)
{
}

device_not_connected::device_not_connected()
: std::runtime_error("")
{
}

device_not_connected::device_not_connected(const device_not_connected& other)
: std::runtime_error(std::string(other.what()))
{
}



