#pragma once
#include "Collections/Declaration/ContainerFilterWrapper-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container>
    ContainerFilterWrapper<Container>
      ::ContainerFilterWrapper(Container& container, const typename iterator::filter_function& filter)
      : _container(container), _filter(filter)
    {
    }

    template<typename Container>
    typename ContainerFilterWrapper<Container>::iterator ContainerFilterWrapper<Container>::begin()
    {
      return iterator(_container.begin(), _container.end(), _filter);
    }

    template<typename Container>
    typename ContainerFilterWrapper<Container>::iterator ContainerFilterWrapper<Container>::end()
    {
      return iterator(_container.end(), _container.end(), _filter);
    }
  }
}