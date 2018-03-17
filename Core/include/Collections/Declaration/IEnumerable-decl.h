/***********************************************************************************************************************
* @file IEnumerable-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's IEnumerable declaration class
**********************************************************************************************************************/

#pragma once
#include "Collections/FilterEnumerator.h"
#include "Collections/TransformEnumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename> class ContainerIteratorWrapper;
    template<typename Container, typename IteratorType>
    class IEnumerable
    {
    public:
      typedef typename IteratorType::value_type value_type;
      typedef typename IteratorType::reference reference;
      typedef typename std::add_const<reference>::type const_reference;
      typedef IteratorType iterator;
      typedef typename std::add_const<iterator>::type const_iterator;
      typedef typename iterator::difference_type difference_type;
      typedef size_t size_type;
      typedef FilterEnumerator<iterator> filter_iterator;

      inline virtual ~IEnumerable(){};

      virtual iterator begin() = 0;
      virtual iterator end() = 0;

      bool any(typename const filter_iterator::filter_function& filter);
      const_iterator cbegin() const;
      const_iterator cend() const;
      reference front() const;

      template<typename ValueType>
      ContainerIteratorWrapper<TransformEnumerator<ValueType, iterator>>
        select(typename const TransformEnumerator<ValueType, iterator>::transform_function& transform);
      ContainerIteratorWrapper<filter_iterator> where(typename const filter_iterator::filter_function& filter);
    };
  }
}