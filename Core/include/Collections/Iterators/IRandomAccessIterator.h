#pragma once
#include "Collections/Iterators/IBidirectionalIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IRandomAccessIterator : public virtual IBidirectionalIterator<T>
      {
      public:
        #pragma region Arithmetic Operators
        virtual IRandomAccessIterator<T>& operator+=(int offset) = 0;
        virtual IRandomAccessIterator<T>& operator-=(int offset) = 0;
        #pragma endregion

        #pragma region Comparison Operators
        virtual bool operator<(const IRandomAccessIterator<T>& rhs) const = 0;
        virtual bool operator<=(const IRandomAccessIterator<T>& rhs) const = 0;
        virtual bool operator>(const IRandomAccessIterator<T>& rhs) const = 0;
        virtual bool operator>=(const IRandomAccessIterator<T>& rhs) const = 0;
        #pragma endregion

        #pragma region Dereference Operator
        virtual std::add_lvalue_reference_t<T> operator[](size_t location) const = 0;
        #pragma endregion
      };
    }
  }
}