#pragma once
#include "Collections/ContainerIteratorWrapper.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    bool IEnumerable<IteratorType>::any(typename const filter_iterator::filter_function& filter)
    {
      for (const auto& value : *this)
      {
        if(filter(value))
          return true;
      }

      return false;
    }

    template<typename IteratorType>
    typename IEnumerable<IteratorType>::const_iterator IEnumerable<IteratorType>::cbegin() const
    {
      return begin();
    }

    template<typename IteratorType>
    typename IEnumerable<IteratorType>::const_iterator IEnumerable<IteratorType>::cend() const
    {
      return end();
    }

    template<typename IteratorType>
    typename IEnumerable<IteratorType>::reference IEnumerable<IteratorType>::front() const
    {
      return *begin();
    }

    template<typename IteratorType>
    ContainerIteratorWrapper<typename IEnumerable<IteratorType>::filter_iterator>
      IEnumerable<IteratorType>::where(typename const filter_iterator::filter_function& filter)
    {
      return ContainerIteratorWrapper<filter_iterator>(filter_iterator(begin(), end(), filter),
                                                       filter_iterator(end(), end(), filter));
    }
  }
}