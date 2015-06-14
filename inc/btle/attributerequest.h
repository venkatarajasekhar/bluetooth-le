
#ifndef btle_attributerequest_h
#define btle_attributerequest_h

#include "btle/error.h"

namespace btle{
    class attributerequest: public base{
    public:
        attributerequest();
        attributerequest(const std::string& value, const error& err);
        attributerequest(const attributerequest& other);
      
    public: //
        
        const error& err() const;
        
    private:
        error err_;
    };
}

#endif
