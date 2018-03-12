#pragma once
#include "Collections/FilterEnumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename> class ContainerIteratorWrapper;
    template<typename IteratorType>
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
      ContainerIteratorWrapper<filter_iterator> where(typename const filter_iterator::filter_function& filter);
    };
  }
}