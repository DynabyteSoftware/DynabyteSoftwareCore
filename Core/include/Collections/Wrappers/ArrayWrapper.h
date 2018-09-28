#pragma once
#include "Collections/IEnumerable.h"
#include "Collections/Wrappers/PointerIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T>
      class ArrayWrapper : public IEnumerable<Iterators::IRandomAccessIterator<T>>
      {
      public:
        #pragma region Constructors
        ArrayWrapper(T arrayObject[], size_t arraySize)
          : _arrayObject(arrayObject), _arraySize(arraySize)
        {
        }
        #pragma endregion

        #pragma region IEnumerable
        virtual Enumerator<Iterators::IRandomAccessIterator<T>> getEnumerator() const override
        {
          T* end = _arrayObject + _arraySize;
          return Enumerator<Iterators::IRandomAccessIterator<T>>(PointerIterator<T>(_arrayObject, _arrayObject, end),
                                                                 PointerIterator<T>(_arrayObject, end, end));
        }
        #pragma endregion
      private:
        T* _arrayObject;
        size_t _arraySize;
      };
    }
  }
}