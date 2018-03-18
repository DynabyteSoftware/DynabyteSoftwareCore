/***********************************************************************************************************************
* @file IEnumerable.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's IEnumerable definition class
**********************************************************************************************************************/

#pragma once
#include "Collections/ContainerIteratorWrapper.h"
#include "Collections/ContainerFilterWrapper.h"
#include "Collections/ContainerTransformWrapper.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container, typename IteratorType>
    bool IEnumerable<Container, IteratorType>::any(typename const filter_iterator::filter_function& filter)
    {
      for (const auto& value : *this)
      {
        if(filter(value))
          return true;
      }

      return false;
    }

    template<typename Container, typename IteratorType>
    typename IEnumerable<Container, IteratorType>::const_iterator IEnumerable<Container, IteratorType>::cbegin() const
    {
      return begin();
    }

    template<typename Container, typename IteratorType>
    typename IEnumerable<Container, IteratorType>::const_iterator IEnumerable<Container, IteratorType>::cend() const
    {
      return end();
    }

    template<typename Container, typename IteratorType>
    typename IEnumerable<Container, IteratorType>::reference IEnumerable<Container, IteratorType>::front() const
    {
      return *begin();
    }

    template<typename Container, typename IteratorType>
    template<typename ValueType>
    ContainerTransformWrapper<Container, ValueType> IEnumerable<Container, IteratorType>
      ::select(typename const TransformEnumerator<ValueType, IteratorType>::transform_function& transform)
    {
      return ContainerTransformWrapper<Container, ValueType>(*dynamic_cast<Container*>(this), transform);
    }

    template<typename Container, typename IteratorType>
    ContainerFilterWrapper<Container>
      IEnumerable<Container, IteratorType>::where(typename const filter_iterator::filter_function& filter)
    {
      return ContainerFilterWrapper<Container>(*dynamic_cast<Container*>(this), filter);
    }
  }
}