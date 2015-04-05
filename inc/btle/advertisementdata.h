#ifndef ADVERTISEMENTDATA_H
#define ADVERTISEMENTDATA_H

#include <string>
#include <map>

#include "btle/base.h"

namespace btle{

    /**
     * @brief The advertisement_type enum
     */
    enum advertisement_type
    {
        GAP_ADTYPE_FLAGS                        = 0x01,
        GAP_ADTYPE_16BIT_MORE                   = 0x02,
        GAP_ADTYPE_16BIT_COMPLETE               = 0x03,
        GAP_ADTYPE_32BIT_MORE                   = 0x04,
        GAP_ADTYPE_32BIT_COMPLETE               = 0x05,
        GAP_ADTYPE_128BIT_MORE                  = 0x06,
        GAP_ADTYPE_128BIT_COMPLETE              = 0x07,
        GAP_ADTYPE_LOCAL_NAME_SHORT             = 0x08,
        GAP_ADTYPE_LOCAL_NAME_COMPLETE          = 0x09,
        GAP_ADTYPE_POWER_LEVEL                  = 0x0A,
        GAP_ADTYPE_OOB_CLASS_OF_DEVICE          = 0x0D,
        GAP_ADTYPE_OOB_SIMPLE_PAIRING_HASHC     = 0x0E,
        GAP_ADTYPE_OOB_SIMPLE_PAIRING_RANDR     = 0x0F,
        GAP_ADTYPE_SM_TK                        = 0x10,
        GAP_ADTYPE_SM_OOB_FLAG                  = 0x11,
        GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE    = 0x12,
        GAP_ADTYPE_SIGNED_DATA                  = 0x13,
        GAP_ADTYPE_SERVICES_LIST_16BIT          = 0x14,
        GAP_ADTYPE_SERVICES_LIST_128BIT         = 0x15,
        GAP_ADTYPE_SERVICE_DATA                 = 0x16,
        GAP_ADTYPE_MANUFACTURER_SPECIFIC        = 0xFF
    };

    class BTLE_API advertisementdata: public base
    {
    public:
        advertisementdata();
        advertisementdata( const std::string& data );
        advertisementdata( const advertisementdata& other );
        advertisementdata& operator = (const advertisementdata& other);
    };
    
    typedef std::map<btle::advertisement_type,btle::advertisementdata> adv_fields;
}

#endif // ADVERTISEMENTDATA_H

