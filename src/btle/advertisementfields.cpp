
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

advertisementfields& advertisementfields::operator << (const std::map<btle::advertisement_type,btle::advertisementdata>& fields)
{
    // process
    for( adv_fields::const_iterator it = fields.begin(); it != fields.end(); ++it )
    {
        fields_[it->first] = it->second;
        switch (it->first) {
            case GAP_ADTYPE_LOCAL_NAME_SHORT:
            case GAP_ADTYPE_LOCAL_NAME_COMPLETE:
            {
                if( it->second.string_value().compare(name_) == std::string::npos )
                {
                    name_ = it->second.string_value();
                }
                break;
            }
            /*case GAP_ADTYPE_16BIT_COMPLETE:
            {
                break;
            }
            case GAP_ADTYPE_16BIT_MORE:
            {
                break;
            }
            case GAP_ADTYPE_128BIT_COMPLETE:
            {
                break;
            }
            case GAP_ADTYPE_128BIT_MORE:
            {
                break;
            }*/
            default:
                break;
        }
        
        /*
         if(uid.is16bit())
         {
         if( advertisement_data_.find(btle::GAP_ADTYPE_16BIT_COMPLETE) == advertisement_data_.end() )
         {
         if( advertisement_data_.find(btle::GAP_ADTYPE_16BIT_MORE) != advertisement_data_.end() )
         {
         return uuid(advertisement_data_.find(btle::GAP_ADTYPE_16BIT_MORE)->second.string_value()) == uid;
         }
         }
         //        else return advertisement_data_[btle::GAP_ADTYPE_16BIT_COMPLETE] == uid;
         }
         else
         {
         if( advertisement_data_.find(btle::GAP_ADTYPE_128BIT_COMPLETE) == advertisement_data_.end() )
         {
         if( advertisement_data_.find(btle::GAP_ADTYPE_128BIT_MORE) != advertisement_data_.end() )
         {
         //                return advertisement_data_[btle::GAP_ADTYPE_128BIT_MORE] == uid;
         }
         }
         //        else return advertisement_data_[btle::GAP_ADTYPE_128BIT_COMPLETE] == uid;
         }
         */
    }
    return *this;
}

const advertisementdata* advertisementfields::operator[](btle::advertisement_type key) const
{
    return fields_.find(key) != fields_.end() ? (const advertisementdata*)&fields_.find(key)->second : NULL;
}

// get
const std::string& advertisementfields::name() const
{
    return name_;
}

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
        //        else return advertisement_data_[btle::GAP_ADTYPE_16BIT_COMPLETE] == uid;
    }
    else
    {
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

