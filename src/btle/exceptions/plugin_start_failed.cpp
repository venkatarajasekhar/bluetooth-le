
#include "btle/exceptions/plugin_start_failed.h"
#include "btle/utility.h"

using namespace btle;
using namespace btle::exceptions;

plugin_start_failed::plugin_start_failed(const std::string& what,int err)
: std::runtime_error(what + " error: " + utility::to_string(err)),
  error_(err)
{
}

plugin_start_failed::plugin_start_failed()
: std::runtime_error(""),
  error_(-1)
{
}

plugin_start_failed::plugin_start_failed(const plugin_start_failed& other)
: std::runtime_error(std::string(other.what())),
  error_(other.error_)
{
}


