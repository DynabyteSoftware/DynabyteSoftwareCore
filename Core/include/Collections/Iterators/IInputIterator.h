#pragma once
#include "Collections/Iterators/IIterator.h"
#include <type_traits>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IInputIterator : public virtual IIterator<T>
      {
      public:
        #pragma region Equatable
        virtual bool operator==(const IInputIterator<T>& rhs) const = 0;
        inline bool operator!=(const IInputIterator<T>& rhs) const { return !operator==(rhs); }
        #pragma endregion

        #pragma region R-Value Dereferenceable
        virtual std::add_lvalue_reference_t<T> operator*() const = 0;
        virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const = 0;
        #pragma endregion
      };
    }
  }
}