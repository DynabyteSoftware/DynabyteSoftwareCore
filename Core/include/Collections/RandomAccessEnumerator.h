#pragma once
#include "Collections/BidirectionalEnumerator.h"
#include "Collections/Iterators/IRandomAccessIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class RandomAccessEnumerator : public BidirectionalEnumerator<T>, public virtual Iterators::IRandomAccessIterator<T>
    {
    public:
      #pragma region Constructors
      RandomAccessEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T> end)
        : RandomAccessEnumerator(begin, begin, end)
      {
      }
      #pragma endregion

      #pragma region Enumerator
      RandomAccessEnumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<RandomAccessEnumerator<T>&>(&rhs))
        {
          Enumerator<T>::operator=(rhs);
          _current = castCurrent< Iterators::IRandomAccessIterator<T> >();
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }
      #pragma endregion

      #pragma region IRandomAccessIterator
      #pragma region Arithmetic Operators
      virtual RandomAccessEnumerator<T>& operator+=(int offset) override
      {
        return _current->operator+=(offset);
      }

      virtual RandomAccessEnumerator<T>& operator-=(int offset) override
      {
        return _current->operator-=(offset);
      }
      #pragma endregion

      #pragma region Comparison Operators
      virtual bool operator<(const IRandomAccessIterator<T>& rhs) const override
      {
        return _current->operator<(rhs);
      }

      virtual bool operator<=(const IRandomAccessIterator<T>& rhs) const override
      {
        return _current->operator<=(rhs);
      }

      virtual bool operator>(const IRandomAccessIterator<T>& rhs) const override
      {
        return _current->operator>(rhs);
      }

      virtual bool operator>=(const IRandomAccessIterator<T>& rhs) const override
      {
        return _current->operator>=(rhs);
      }
      #pragma endregion

      #pragma region Dereference Operator
      virtual std::add_lvalue_reference_t<T> operator[](size_t location) const override
      {
        return _current->operator[](location);
      }
      #pragma endregion
      #pragma endregion
    private:
      #pragma region Constructors
      RandomAccessEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                      const Iterators::IIterator<T> end)
        : BidirectionalEnumerator<T>(begin, current, end), 
          _current(castCurrent< Iterators::IRandomAccessIterator<T> >())
      {
      }
      #pragma endregion

      #pragma region Variables
      Iterators::IRandomAccessIterator<T>* _current;
      #pragma endregion

      #pragma region Enumerator
      std::unique_ptr<Iterators::IIterator<T>> clone() override
      {
        return std::make_unique< RandomAccessEnumerator<T> >(*_begin, *_current, *_end);
      }
      #pragma endregion
    };
  }
}