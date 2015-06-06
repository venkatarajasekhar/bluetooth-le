#ifndef ATOMICLIST_HPP
#define ATOMICLIST_HPP

template <typename T>
atomiclist<T>::atomiclist()
: list_(),
  mutex_()
{
}

template <typename T>
void atomiclist<T>::push_back(const T& object)
{
    std::unique_lock<std::mutex> lock(mutex_);
    list_.push_back(object);
}

template <typename T>
size_t atomiclist<T>::size()
{
    mutex_.lock();
    size_t size(list_.size());
    mutex_.unlock();
    return size;
}

template <typename T>
T atomiclist<T>::take_front()
{
    mutex_.lock();
    T = list_.front();
    list_.pop_front();
    mutex_.unlock();
    return T;
}

#endif // ATOMICLIST_HPP

