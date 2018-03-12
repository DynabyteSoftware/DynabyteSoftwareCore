#pragma once
#include "Collections/Definitions/ContainerIteratorWrapper-def.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    ContainerIteratorWrapper<IteratorType>::ContainerIteratorWrapper(const IteratorType& begin,
                                                                     const IteratorType& end)
      : _begin(begin), _end(end)
    {
    }

    template<typename IteratorType>
    typename ContainerIteratorWrapper<IteratorType>::iterator ContainerIteratorWrapper<IteratorType>::begin()
    {
      return _begin;
    }

    template<typename IteratorType>
    typename ContainerIteratorWrapper<IteratorType>::iterator ContainerIteratorWrapper<IteratorType>::end()
    {
      return _end;
    }
  }
}