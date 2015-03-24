#ifndef CENTRALPLUGINREGISTERER_HPP
#define CENTRALPLUGINREGISTERER_HPP

#include "btle/central/centralpluginfactory.h"
#include "btle/central/centralplugininterface.h"

using namespace btle::central;

template<typename T>
centralplugininterface* centralpluginregisterer<T>::constructor()
{
    return new T();
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

#endif // CENTRALPLUGINREGISTERER_HPP

