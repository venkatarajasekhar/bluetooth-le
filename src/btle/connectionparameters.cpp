

#include "btle/connectionparameters.h"
#include "btle/utility.h"

namespace {
    #define INTERVAL_MULTIPLYER 1.25
}

using namespace btle;

connectionparameters::connectionparameters()
: base("","Connection parameters not available!"),
  connection_interval_(0),
  connection_latency_(0),
  connection_timeout_(0)
{
}

connectionparameters::connectionparameters(
    uint16_t connection_interval,
    uint16_t connection_latency,
    uint16_t connection_timeout)
: base("","Connection parameters interval: " + utility::to_string(connection_interval*1.25) +
          " Latency: " + utility::to_string(connection_latency) +
          " Timeout: " + utility::to_string(connection_timeout)),
  connection_interval_(connection_interval),
  connection_latency_(connection_latency),
  connection_timeout_(connection_timeout)
{
}
