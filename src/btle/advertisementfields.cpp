
#include "btle/advertisementfields.h"

using namespace btle;

advertisementfields::advertisementfields()
: base("","Advertisement data processor class"),
  fields_(),
  name_(),
  advertiset_services_()
{
}

advertisementfields::advertisementfields(const advertisementfields& other)
: base(other),
  fields_(),
  name_(),
  advertiset_services_()
{
}

advertisementfields& advertisementfields::operator << (const std::map<btle::advertisement_data_type,btle::advertisementdata>& fields)
{
    for( adv_fields::const_iterator it = fields.begin(); it != fields.end(); ++it )
    {
        fields_[it->first] = it->second;
        switch (it->first) {
            case GAP_ADTYPE_LOCAL_NAME_SHORT:
            case GAP_ADTYPE_LOCAL_NAME_COMPLETE:
            {
                if( it->second.string_value().compare(name_) != std::string::npos )
                {
                    name_ = it->second.string_value();
                }
                break;
            }
            default:
                break;
        }
    }
    return *this;
}

const advertisementdata* advertisementfields::operator[](btle::advertisement_data_type key) const
{
    return fields_.find(key) != fields_.end() ? (const advertisementdata*)&fields_.find(key)->second : NULL;
}

/**
 * @brief advertisementfields::name
 * @return gap local name from advertisement if any or empty string
 */
const std::string& advertisementfields::name() const
{
    return name_;
}

/**
 * @brief advertisementfields::is_service_advertiset
 * @param uid
 * @return true is uuid is found from advertisement fields, NOTE
 *         this function returns true is the service has been adrvertiset at some point and
 *         device data has not been invalidated at any time
 */
bool advertisementfields::is_service_advertiset( const btle::uuid& uid ) const
{
    if(uid.is16bit())
    {
        if( fields_.find(btle::GAP_ADTYPE_16BIT_COMPLETE) == fields_.end() )
        {
            if( fields_.find(btle::GAP_ADTYPE_16BIT_MORE) != fields_.end() )
            {
                return uuid(fields_.find(btle::GAP_ADTYPE_16BIT_MORE)->second.string_value()) == uid;
            }
        }
        else return uuid(fields_.find(btle::GAP_ADTYPE_16BIT_COMPLETE)->second.string_value()) == uid;;
    }
    else
    {
        // TODO impelemt
        if( fields_.find(btle::GAP_ADTYPE_128BIT_COMPLETE) == fields_.end() )
        {
            if( fields_.find(btle::GAP_ADTYPE_128BIT_MORE) != fields_.end() )
            {
                //                return advertisement_data_[btle::GAP_ADTYPE_128BIT_MORE] == uid;
            }
        }
        //        else return advertisement_data_[btle::GAP_ADTYPE_128BIT_COMPLETE] == uid;
    }
    return false;
}

void advertisementfields::clear()
{
    fields_.clear();
    name_ = "";
}


