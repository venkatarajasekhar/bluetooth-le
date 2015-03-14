#ifndef BASE_H
#define BASE_H

#include <string>
#include "btle/btle_global.h"

namespace btle {
    /**
     * @brief The base class, common base class for most btle lib classes
     */
    class BTLE_API base
    {
    public:
        base();
        base(const std::string& value);
        base(const std::string& value,
             const std::string& description);
        base(const base& other);
        ~base();

    public:

        virtual bool operator == (const base& other);
        virtual std::string to_string() const;
        virtual int to_int(int base = 10);

    public:

        const std::string& string_value() const;
        const std::string& description() const;
        void set_string_value(const std::string& value);

    protected:
        std::string value_;
        std::string description_;
    };
}

#endif // BASE_H
