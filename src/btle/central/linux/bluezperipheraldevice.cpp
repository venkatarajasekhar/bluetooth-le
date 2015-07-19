
#include "btle/central/linux/bluezperipheraldevice.h"

using namespace btle;
using namespace btle::central;
using namespace btle::central::linux_platform;

bluezperipheraldevice::bluezperipheraldevice(const bda &addr)
: device(addr)
{
}
