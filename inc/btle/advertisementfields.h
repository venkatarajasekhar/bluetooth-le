#ifndef btle_advertisementfields_h
#define btle_advertisementfields_h

#include "btle/base.h"
#include "btle/uuid.h"
#include "btle/advertisementdata.h"
// system
#include <map>

namespace btle {
    /**
     * @brief The advertisementfields class, general purpose advertisement fields "processor"
     */
    class advertisementfields: public base
    {
    public:
        advertisementfields();
        advertisementfields(const advertisementfields& other);
        
        // operators
        advertisementfields& operator << (const std::map<btle::advertisement_data_type,btle::advertisementdata>& fields);
        const advertisementdata* operator[](btle::advertisement_data_type key) const;
        
        // get
        const std::string& name() const;
        bool is_service_advertiset( const btle::uuid& uid ) const;

    public: // from base

        void invalidate();
        
    private:
        std::map<btle::advertisement_data_type,btle::advertisementdata> fields_;
        std::string name_;
        uuid_list advertiset_services_;
    };
}

#endif
