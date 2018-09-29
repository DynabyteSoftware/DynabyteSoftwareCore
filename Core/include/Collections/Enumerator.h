#pragma once
#include "Collections/Iterators/IIterator.h"
#include "Exception.h"
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
      Enumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& end)
        : Enumerator(begin, begin, end)
      {
      }

      Enumerator(const Enumerator<T>& original)
        : Enumerator(*original._begin, *original._current, *original._end)
      {
      }

      Enumerator(Enumerator<T>&& old)
        : _begin(std::move(old._begin)), _current(std::move(old._current)), _end(std::move(old._end))
      {
      }
      #pragma endregion

      #pragma region Observers
      const Iterators::IIterator<T>& getBegin() const
      {
        return *_begin;
      }

      const Iterators::IIterator<T>& getEnd() const
      {
        return *_end;
      }
      #pragma endregion

      #pragma region IIterator
      Enumerator<T>& operator=(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<const Enumerator<T>*>(&rhs))
        {
          _begin = iterator->_begin->clone(getUniversalKey());
          _end = iterator->_end->clone(getUniversalKey());
          _current = iterator->_current->clone(getUniversalKey());
          return *this;
        }

        THROW(Exception, "iterator not an enumerator")
      }

      Enumerator<T>& operator++() override
      {
        if(_current.get() == _end.get())
          THROW(Exception, "Attempted to advance past end of container")

        _current->operator++();
        return *this;
      }

      Enumerator<T>& operator++(int value) override
      {
        if(_current.get() == _end.get())
          THROW(Exception, "Attempted to advance past end of container")

        _current->operator++(value);
        return *this;
      }
      #pragma endregion
    protected:
      #pragma region Constructors
      Enumerator(const Iterators::IIterator<T>& begin, const Iterators::IIterator<T>& current,
                 const Iterators::IIterator<T>& end)
        : _begin(begin.clone(getUniversalKey())), _end(end.clone(getUniversalKey())),
          _current(current.clone(getUniversalKey()))
      {
      }
      #pragma endregion

      #pragma region Observers
      template<typename IteratorType>
      IteratorType* castCurrent()
      {
        return dynamic_cast<IteratorType*>(_current.get());
      }
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr< const Iterators::IIterator<T> > _begin;
      std::unique_ptr< const Iterators::IIterator<T> > _end;
      std::unique_ptr<Iterators::IIterator<T>> _current;
      #pragma endregion

      #pragma region IIterator
      std::unique_ptr<Iterators::IIterator<T>>
      clone(const typename AccessControl::AccessKeychain< Iterators::IIterator<T> >::AccessKey&) const override
      {
        return std::make_unique< Enumerator<T> >(*this);
      }
      #pragma endregion
    };
  }
}