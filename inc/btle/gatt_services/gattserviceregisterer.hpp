#ifndef GATTSERVICEREGISTERER_HPP
#define GATTSERVICEREGISTERER_HPP

#include "btle/gatt_services/gattservicefactory.h"

using namespace btle::gatt_services;

template<typename T>
gattservicebase* gattserviceregisterer<T>::constructor()
{
    // TODO fix later use copy constructor
    return new T();
}

template<typename T>
gattserviceregisterer<T>::gattserviceregisterer()
{
    gattservicefactory& instance = gattservicefactory::instance();
    instance.insert(constructor);
}

template<typename T>
gattserviceregisterer<T>::~gattserviceregisterer()
{
}

#endif
