#pragma once
#include "Enumerator.h"
#include "Exception.h"
#include "Iterators/IInputIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class InputEnumerator
      : public Enumerator<T>,
        public virtual Iterators::IInputIterator<T>
    {
    public:
      #pragma region Constructors
      public InputEnumerator(const IInputIterator<T> iterator)
        : Enumerator<T>(iterator),
          _iterator(castIterator())
      {
      }
      #pragma endregion

      #pragma region Enumerator
      InputEnumerator& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto& iterator = dynamic_cast<const Iterators::IInputIterator<T>&>(rhs))
        {
          Enumerator<T>::operator=(iterator);
          _iterator = castIterator();
          return *this;
        }

        THROW(Exception, "Iterator not an input iterator")
      }
      #pragma endregion
    private:
      #pragma region Variables
      Iterators::IInputIterator<T>* _iterator;
      #pragma endregion

      #pragma region Observers
      inline Iterators::IInputIterator<T>* castIterator() const
      {
        return dynamic_cast<Iterators::IInputIterator<T>*>(Enumerator<T>::_iterator.get());
      }
      #pragma endregion
    };
  }
}