#pragma once
#include "Collections/Enumerator.h"
#include "Collections/Iterators/IOutputIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class OutputEnumerator : public Enumerator<T>, public virtual Iterators::IOutputIterator<T>
    {
    public:
      #pragma region Constructors
      OutputEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T> end)
        : OutputEnumerator(begin, begin, end)
      {
      }
      #pragma endregion

      #pragma region Enumerator
      OutputEnumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<OutputEnumerator<T>&>(&rhs))
        {
          Enumerator<T>::operator=(rhs);
          _current = castCurrent< Iterators::IOutputIterator<T> >();
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }
      #pragma endregion

      #pragma region IOutputIterator
      #pragma region R-Value Dereferenceable
      virtual std::add_lvalue_reference_t<T> operator*() const override
      {
        return *_current;
      }

      virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const override
      {
        return _current->operator->();
      }
      #pragma endregion
      #pragma endregion
    private:
      #pragma region Constructors
      OutputEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                       const Iterators::IIterator<T> end)
        : Enumerator<T>(begin, current, end), 
          _current(castCurrent< Iterators::IOutputIterator<T> >())
      {
      }
      #pragma endregion

      #pragma region Variables
      Iterators::IOutputIterator<T>* _current;
      #pragma endregion

      #pragma region Enumerator
      std::unique_ptr<Iterators::IIterator<T>> clone() override
      {
        return std::make_unique< OutputEnumerator<T> >(*_begin, *_current, *_end);
      }
      #pragma endregion
    };
  }
}