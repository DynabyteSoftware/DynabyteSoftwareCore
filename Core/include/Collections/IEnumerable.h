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
    ContainerIteratorWrapper<TransformEnumerator<ValueType, IteratorType>>
      IEnumerable<Container, IteratorType>
      ::select(typename const TransformEnumerator<ValueType, IteratorType>::transform_function& transform)
    {
      return
        ContainerIteratorWrapper<
          TransformEnumerator<ValueType,
                              IteratorType>>(TransformEnumerator<ValueType, IteratorType>(begin(), transform),
                                             TransformEnumerator<ValueType, IteratorType>(end(), transform));
    }

    template<typename Container, typename IteratorType>
    ContainerIteratorWrapper<typename IEnumerable<Container, IteratorType>::filter_iterator>
      IEnumerable<Container, IteratorType>::where(typename const filter_iterator::filter_function& filter)
    {
      return ContainerIteratorWrapper<filter_iterator>(filter_iterator(begin(), end(), filter),
                                                       filter_iterator(end(), end(), filter));
    }
  }
}