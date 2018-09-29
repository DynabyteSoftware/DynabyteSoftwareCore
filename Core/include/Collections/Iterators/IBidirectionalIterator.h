#pragma once
#include "Collections/Iterators/IForwardIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IBidirectionalIterator : public virtual IForwardIterator<T>
      {
      public:
        #pragma region Assignable
        IBidirectionalIterator<T>& operator=(const IBidirectionalIterator<T>& rhs)
        {
          assign(rhs);
          return *this;
        }
        #pragma endregion

        #pragma region Decrementable
        virtual IBidirectionalIterator<T>& operator--() = 0;
        virtual IBidirectionalIterator<T>& operator--(int) = 0;
        #pragma endregion
      };
    }
  }
}