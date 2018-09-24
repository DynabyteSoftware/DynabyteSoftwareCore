#pragma once
#include "Collections/Iterators/IBidirectionalIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class Enumerator : public virtual Iterators::IIterator<T>
    {
    public:
      #pragma region Constructors
      Enumerator(const Iterators::IIterator<T>& iterator)
        : _iterator(iterator.clone())
      {
      }
      #pragma endregion

      #pragma region IIterator
      Enumerator& operator=(const Iterators::IIterator<T>& rhs) override
      {
        _iterator = rhs.clone();
      }

      Enumerator& operator++() override
      {
        _iterator->operator++();
        return *this;
      }

      Enumerator& operator++(int value) override
      {
        _iterator->operator++(value);
        return *this;
      }
      #pragma endregion
    protected:
      #pragma region Variables
      std::unique_ptr<Iterators::IIterator<T>> _iterator;
      #pragma endregion
    private:
      #pragma region IIterator
      std::unique_ptr<Iterators::IIterator<T>> clone() override
      {
        return std::make_unique< Enumerator<T> >(*_iterator);
      }
      #pragma endregion
    };
  }
}