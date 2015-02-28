
#include "btle/device.h"

using namespace btle;

device::device()
{
}

device::~device()
{
}

const std::string& device::name()
{
    return name_;
}

const advertisementdata* device::advertisement_data_for_key(btle::advertisement_type key) const
{
    if( advertisement_data_.find(key) != advertisement_data_.end() ){
        return (const advertisementdata*)&advertisement_data_.find(key)->second;
    }
    else return NULL;
}

gattdatabase& device::db()
{
    return db_;
}

connection_state device::state() const
{
    return state_;
}
