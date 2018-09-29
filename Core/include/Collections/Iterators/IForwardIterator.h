#pragma once
#include "Collections/Iterators/IInputIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IForwardIterator
        : public virtual IInputIterator<T>
      {
      public:
        #pragma region Assignable
        IForwardIterator<T>& operator=(const IForwardIterator<T>& rhs)
        {
          assign(rhs);
          return *this;
        }
        #pragma endregion
      };
    }
  }
}