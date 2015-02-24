#ifndef ADVERTISEMENTDATA_H
#define ADVERTISEMENTDATA_H

#include <string>
#include "btle/base.h"

namespace btle{

    /**
     * @brief The advertisement_type enum
     */
    enum advertisement_type
    {
        GAP_ADTYPE_FLAGS                        = 0x01, //!< Discovery Mode: @ref GAP_ADTYPE_FLAGS_MODES
        GAP_ADTYPE_16BIT_MORE                   = 0x02, //!< Service: More 16-bit UUIDs available
        GAP_ADTYPE_16BIT_COMPLETE               = 0x03, //!< Service: Complete list of 16-bit UUIDs
        GAP_ADTYPE_32BIT_MORE                   = 0x04, //!< Service: More 32-bit UUIDs available
        GAP_ADTYPE_32BIT_COMPLETE               = 0x05, //!< Service: Complete list of 32-bit UUIDs
        GAP_ADTYPE_128BIT_MORE                  = 0x06, //!< Service: More 128-bit UUIDs available
        GAP_ADTYPE_128BIT_COMPLETE              = 0x07, //!< Service: Complete list of 128-bit UUIDs
        GAP_ADTYPE_LOCAL_NAME_SHORT             = 0x08, //!< Shortened local name
        GAP_ADTYPE_LOCAL_NAME_COMPLETE          = 0x09, //!< Complete local name
        GAP_ADTYPE_POWER_LEVEL                  = 0x0A, //!< TX Power Level: 0xXX: -127 to +127 dBm
        GAP_ADTYPE_OOB_CLASS_OF_DEVICE          = 0x0D, //!< Simple Pairing OOB Tag: Class of device (3 octets)
        GAP_ADTYPE_OOB_SIMPLE_PAIRING_HASHC     = 0x0E, //!< Simple Pairing OOB Tag: Simple Pairing Hash C (16 octets)
        GAP_ADTYPE_OOB_SIMPLE_PAIRING_RANDR     = 0x0F, //!< Simple Pairing OOB Tag: Simple Pairing Randomizer R (16 octets)
        GAP_ADTYPE_SM_TK                        = 0x10, //!< Security Manager TK Value
        GAP_ADTYPE_SM_OOB_FLAG                  = 0x11, //!< Secutiry Manager OOB Flags
        GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE    = 0x12, //!< Min and Max values of the connection interval (2 octets Min, 2 octets Max) (0xFFFF indicates no conn interval min or max)
        GAP_ADTYPE_SIGNED_DATA                  = 0x13, //!< Signed Data field
        GAP_ADTYPE_SERVICES_LIST_16BIT          = 0x14, //!< Service Solicitation: list of 16-bit Service UUIDs
        GAP_ADTYPE_SERVICES_LIST_128BIT         = 0x15, //!< Service Solicitation: list of 128-bit Service UUIDs
        GAP_ADTYPE_SERVICE_DATA                 = 0x16, //!< Service Data
        GAP_ADTYPE_MANUFACTURER_SPECIFIC        = 0xFF //!< Manufacturer Specific Data: first 2 octets contain the Company Identifier Code followed by the additional manufacturer specific data
    };

    class advertisementdata: public base
    {
    public:
        advertisementdata();
        advertisementdata(const std::string& data);
        advertisementdata( const advertisementdata& other );
        advertisementdata& operator = (const advertisementdata& other);
    };
}

#endif // ADVERTISEMENTDATA_H

