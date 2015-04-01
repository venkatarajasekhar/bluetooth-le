#ifndef CENTRALPLUGINREGISTERER_HPP
#define CENTRALPLUGINREGISTERER_HPP

#include "btle/central/centralpluginfactory.h"
#include "btle/central/centralplugininterface.h"
#include "btle/central/centralpluginobserver.h"

using namespace btle::central;

template<typename T>
centralplugininterface* centralpluginregisterer<T>::constructor(centralpluginobserver& observer)
{
    return new T(observer);
}

template<typename T>
centralpluginregisterer<T>::centralpluginregisterer()
{
    centralpluginfactory::instance().insert(&constructor);
}

template<typename T>
centralpluginregisterer<T>::~centralpluginregisterer()
{
}

#endif

