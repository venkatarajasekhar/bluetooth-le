#ifndef ATOMICLIST_H
#define ATOMICLIST_H

#include <deque>
#include <mutex>

namespace btle {
    template<typename T>
    /**
     * @brief The atomiclist class, general purpose atomic list for all atomic use
     */
    class atomiclist
    {
    public:
        typedef typename std::deque<T>::iterator list_iterator;
        typedef typename std::deque<T>::const_iterator list_iterator_const;

        atomiclist();
        void push_back(const T& object);
        size_t size();
        T take_front();

    private:

        std::deque<T> list_;
        std::mutex mutex_;
    };

    #include "atomiclist.hpp"
}

#endif // ATOMICLIST_H

