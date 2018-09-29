#pragma once
#include "Collections/ForwardEnumerator.h"
#include "Collections/Iterators/IBidirectionalIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class BidirectionalEnumerator : public ForwardEnumerator<T>, public virtual Iterators::IBidirectionalIterator<T>
    {
    public:
      #pragma region Constructors
      BidirectionalEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T> end)
        : BidirectionalEnumerator(begin, begin, end)
      {
      }
      #pragma endregion

      #pragma region Enumerator
      BidirectionalEnumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<BidirectionalEnumerator<T>&>(&rhs))
        {
          Enumerator<T>::operator=(rhs);
          _current = castCurrent< Iterators::IBidirectionalIterator<T> >();
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }
      #pragma endregion

      #pragma region IBidirectionIterator
      #pragma region Decrementable
      virtual BidirectionalEnumerator<T>& operator--() override
      {
        if (_current == &getBegin())
          THROW(Exception, "Attempt to decrement iterator to before beginning")

        _current->operator--();
        return *this;
      }

      virtual BidirectionalEnumerator<T>& operator--(int value) override
      {
        if (_current == &getBegin())
          THROW(Exception, "Attempt to decrement iterator to before beginning")

        _current->operator--(value);
        return *this;
      }
      #pragma endregion
      #pragma endregion
    private:      
      #pragma region Constructors
      BidirectionalEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                      const Iterators::IIterator<T> end)
        : ForwardEnumerator<T>(begin, current, end), 
          _current(castCurrent< Iterators::IBidirectionalIterator<T> >())
      {
      }
      #pragma endregion

      #pragma region Variables
      Iterators::IBidirectionalIterator<T>* _current;
      #pragma endregion

      #pragma region Enumerator
      std::unique_ptr<Iterators::IIterator<T>> clone() override
      {
        return std::make_unique< BidirectionalEnumerator<T> >(*_begin, *_current, *_end);
      }
      #pragma endregion
    };
  }
}