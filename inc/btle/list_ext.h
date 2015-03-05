#ifndef LIST_EXT_H
#define LIST_EXT_H

#include <deque>

namespace btle {
    template<typename T>
    class list_ext{
        typedef bool (*kComparator)( const T& first, const T& second );
        typedef typename std::deque<T>::iterator list_iterator;
        typedef typename std::deque<T>::const_iterator list_const_iterator;
        static bool default_compare(const T& first, const T& second)
        {
            return first == second;
        }

        list_ext();
        list_ext& operator << (const T& object);
        list_ext& operator << (const cslist& other);
        const std::deque<T>& operator()() const;
        std::deque<T>& operator()();
        void set_compare(kComparator comp);
        bool contains(const T& object) const;
        T* fetch();
        void remove( const T& object );

    private:

        std::deque<T> list_;
        kComparator comp_;
    };

    #include "list_ext.hpp"
}

#endif // LIST_H

