#pragma once
#include "Collections/Enumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class IEnumerable
    {
    public:
      inline virtual ~IEnumerable() {};

      Enumerator<T> begin() const
      {
        return getEnumerator();
      }

      Enumerator<T> end() const
      {
        return getEnumerator().getEnd();
      }

      virtual Enumerator<T> getEnumerator() const = 0;
    };
  }
}