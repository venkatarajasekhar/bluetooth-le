#ifndef PERIPHERALPLUGINREGISTERER_HPP
#define PERIPHERALPLUGINREGISTERER_HPP

#include "btle/peripheral/peripheralpluginfactory.h"
#include "btle/peripheral/peripheralplugininterface.h"
#include "btle/peripheral/peripheralpluginobserver.h"

using namespace btle::peripheral;

template<typename T>
peripheralplugininterface* peripheralpluginregisterer<T>::constructor(peripheralpluginobserver& observer)
{
    return new T(observer);
}

template<typename T>
peripheralpluginregisterer<T>::peripheralpluginregisterer()
{
    //peripheralpluginfactory::instance().insert(&constructor);
}

template<typename T>
peripheralpluginregisterer<T>::~peripheralpluginregisterer()
{
}

#endif // PERIPHERALPLUGINREGISTERER_HPP

