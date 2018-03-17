#pragma once
#include "Collections/Declaration/ContainerTransformWrapper-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container, typename ValueType>
    ContainerTransformWrapper<Container, ValueType>
      ::ContainerTransformWrapper(Container& container, const typename iterator::transform_function& transform)
      : _container(container), _transform(transform)
    {
    }

    template<typename Container, typename ValueType>
    typename ContainerTransformWrapper<Container, ValueType>::iterator
      ContainerTransformWrapper<Container, ValueType>::begin()
    {
      return iterator(_container.begin(), _transform);
    }

    template<typename Container, typename ValueType>
    typename ContainerTransformWrapper<Container, ValueType>::iterator
      ContainerTransformWrapper<Container, ValueType>::end()
    {
      return iterator(_container.end(), _transform);
    }
  }
}