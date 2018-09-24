#pragma once
#include "Collections/Iterators/IInputIterator.h"
#include <type_traits>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IOutputIterator : public virtual IIterator<T>
      {
        static_assert(!std::is_const_v<T>, "Output iterators cannot be used with const types");

      public:
        #pragma region L-Value Dereferenceable
        virtual std::add_lvalue_reference_t<T> operator*() const = 0;
        virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const = 0;
        #pragma endregion
      };
    }
  }
}