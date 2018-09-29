#pragma once
#include "Collections/Enumerator.h"
#include "Collections/Iterators/IInputIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class InputEnumerator : public Enumerator<T>, public virtual Iterators::IInputIterator<T>
    {
    public:
      #pragma region Constructors
      InputEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& end)
        : InputEnumerator(begin, begin, end)
      {
      }

      InputEnumerator(const InputEnumerator<T>& original)
        : InputEnumerator(original.getBegin(), *original._current, original.getEnd())
      {
      }

      InputEnumerator(InputEnumerator<T>&& old)
        : Enumerator<T>(std::forward< InputEnumerator<T> >(old)),
          _current(castCurrent< Iterators::IInputIterator<T> >())
      {
      }

      #pragma endregion

      #pragma region Enumerator
      InputEnumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<const InputEnumerator<T>*>(&rhs))
        {
          Enumerator<T>::operator=(rhs);
          _current = castCurrent< Iterators::IInputIterator<T> >();
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }
      #pragma endregion

      #pragma region IInputIterator
      #pragma region Equatable
      virtual bool operator==(const IInputIterator<T>& rhs) const override
      {
        if(const auto* iterator = dynamic_cast<const InputEnumerator<T>*>(&rhs))
        {
          return iterator->_current == _current;
        }

        return false;
      }
      #pragma endregion

      #pragma region R-Value Dereferenceable
      virtual std::add_lvalue_reference_t<T> operator*() const override
      {
        return _current->operator*();
      }

      virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const override
      {
        return _current->operator->();
      }
      #pragma endregion
      #pragma endregion
    protected:
      #pragma region Constructors
      InputEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                      const Iterators::IIterator<T>& end)
        : Enumerator<T>(begin, current, end), 
          _current(castCurrent< Iterators::IInputIterator<T> >())
      {
      }
      #pragma endregion
    private:
      #pragma region Variables
      Iterators::IInputIterator<T>* _current;
      #pragma endregion

      #pragma region Enumerator
      std::unique_ptr<Iterators::IIterator<T>>
      clone(const typename AccessControl::AccessKeychain< Iterators::IIterator<T> >::AccessKey&) const override
      {
        return std::make_unique< InputEnumerator<T> >(*this);
      }
      #pragma endregion
    };
  }
}