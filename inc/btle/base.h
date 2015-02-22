#ifndef BASE_H
#define BASE_H

#include <string>

namespace btle {
    /**
     * @brief The base class, common base class for most btle lib classes
     */
    class base
    {
    public:
        base();
        base(const std::string& value,
             const std::string& description);
        base(const base& other);
        ~base();

    public:

        /**
         * @brief operator == , needed for lib internal template class usage
         * @param other
         * @return
         */
        virtual bool operator == (const base& other);
        virtual std::string to_string() const;
        virtual int to_int(int base = 10);

    public:

        const std::string& string_value() const;
        const std::string& description() const;

    protected:
        std::string _value;
        std::string _description;
    };
}

#endif // BASE_H
