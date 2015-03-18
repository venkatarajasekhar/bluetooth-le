#ifndef ERROR_H
#define ERROR_H

#include "btle/base.h"

namespace btle {
    class BTLE_API error: public base{
    public:
        error();
        error(const error& other);
        error(int code);
        error(int code,const std::string& description);

    public: //

        int code() const;
        bool operator == (const error& other) const;

    private:

        /**
         * @brief code_, error code if any, NOTE this is platform/plugin specific
         */
        int code_;
    };
}

#endif // ERROR_H

