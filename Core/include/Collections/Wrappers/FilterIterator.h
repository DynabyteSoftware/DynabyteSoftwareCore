#pragma once
#include "Collections/Enumerator.h"
#include "Collections/Iterators/IForwardIterator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T>
      class FilterIterator final : public Iterators::IForwardIterator<T>
      {
      public:
        #pragma region Transform Function
        typedef std::function<bool(std::add_lvalue_reference_t<T> value)> filter_function;
        #pragma endregion

        #pragma region Constructors
        FilterIterator(const Enumerator<T>& enumerator, const filter_function& filterFunction)
          : _enumerator(enumerator), _filterFunction(filterFunction)
        {
        }
        #pragma endregion

        #pragma region IForwardIterator
        #pragma endregion
      private:
        Enumerator<T> _enumerator;
        filter_function _filterFunction;
      };
    }
  }
}