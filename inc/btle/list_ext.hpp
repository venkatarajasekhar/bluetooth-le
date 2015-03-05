#ifndef LIST_EXT_HPP
#define LIST_EXT_HPP

template <typename T>
list_ext<T>::list_ext()
: list_(),
  comp_(&list_ext::default_compare)
{
}

template <typename T>
list_ext<T>& list_ext<T>::operator << (const list_ext& other)
{
    list_ = other();
    return *this;
}

template <typename T>
bool list_ext<T>::contains(const T& object) const
{
    for( list_ext<T>::list_const_iterator it=list_.begin(); it!=list_.end(); ++it )
        if( comp_(object,(*it)) ) return true;
    return false;
}

template <typename T>
list_ext<T>& list_ext<T>::operator << (const T& object)
{
    list_.push_back(object);
    return *this;
}

template <typename T>
const std::deque<T>& list_ext<T>::operator()() const
{
    return list_;
}

template <typename T>
std::deque<T>& list_ext<T>::operator()()
{
    return list_;
}

template <typename T>
void list_ext<T>::set_compare(kCustomCompare comp)
{
    comp_ = comp;
}

template<typename T>
T* list_ext<T>::fetch()
{
    // TODO
    return NULL;
}

template <typename T>
void list_ext<T>::remove( const T& object )
{
    for( list_ext<T>::list_iterator it=list_.begin(); it!=list_.end(); ++it )
        if( comp_(object,(*it)) ){ list_.erase(it); return; }
}

#endif // LIST_EXT_HPP

