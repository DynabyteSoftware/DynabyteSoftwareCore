#pragma once
#include "Enumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    class IEnumerable
    {
    public:
      inline virtual ~IEnumerable() {};

      IteratorType& begin()
      {
        return getEnumerator();
      }

      const IteratorType& end()
      {
        return getEnumerator().end();
      }

      virtual Enumerator<IteratorType> getEnumerator() const = 0;
    };
  }
}