#pragma once
#include "Collections/InputEnumerator.h"
#include "Collections/Iterators/IForwardIterator.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class ForwardEnumerator : public InputEnumerator<T>, public virtual Iterators::IForwardIterator<T>
    {
    public:
      #pragma region Constructors
      ForwardEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& end)
        : ForwardEnumerator(begin, begin, end)
      {
      }

      ForwardEnumerator(const ForwardEnumerator<T>& original)
        : ForwardEnumerator(original.getBegin(), *original._current, original.getEnd())
      {
      }

      ForwardEnumerator(ForwardEnumerator<T>&& old)
        : InputEnumerator<T>(std::forward< ForwardEnumerator<T> >(old)),
          _current(castCurrent< Iterators::IForwardIterator<T> >())
      {
      }
      #pragma endregion

      #pragma region Enumerator
      ForwardEnumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<const ForwardEnumerator<T>*>(&rhs))
        {
          Enumerator<T>::operator=(rhs);
          _current = castCurrent< Iterators::IForwardIterator<T> >();
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }
      #pragma endregion
    protected:
      #pragma region Constructors
      ForwardEnumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                      const Iterators::IIterator<T>& end)
        : InputEnumerator<T>(begin, current, end), 
          _current(castCurrent< Iterators::IForwardIterator<T> >())
      {
      }
      #pragma endregion
    private:
      #pragma region Variables
      Iterators::IForwardIterator<T>* _current;
      #pragma endregion

      #pragma region Enumerator
      std::unique_ptr<Iterators::IIterator<T>>
      clone(const typename AccessControl::AccessKeychain< Iterators::IIterator<T> >::AccessKey&) const override
      {
        return std::make_unique< ForwardEnumerator<T> >(*this);
      }
      #pragma endregion
    };
  }
}