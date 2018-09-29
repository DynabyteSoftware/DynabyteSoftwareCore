#pragma once
#include "Collections/ForwardEnumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class IEnumerable
    {
    public:
      inline virtual ~IEnumerable() {};

      ForwardEnumerator<T> begin() const
      {
        return getEnumerator();
      }

      ForwardEnumerator<T> end() const
      {
        const auto& iterator = getEnumerator().getEnd();
        return ForwardEnumerator<T>(iterator, iterator);
      }

      virtual ForwardEnumerator<T> getEnumerator() const = 0;
    };
  }
}