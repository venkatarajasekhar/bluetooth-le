
#include "btle/peripheral/apple/corebluetoothcentraldevice.h"

using namespace btle;
using namespace btle::peripheral::apple;

corebluetoothcentraldevice::corebluetoothcentraldevice(CBCentral* central)
: device(bda("00:00:00:00:00:00")),
  central_(central)
{
    
}

CBCentral* corebluetoothcentraldevice::central()
{
    return central_;
}

