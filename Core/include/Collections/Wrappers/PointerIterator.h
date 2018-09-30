#pragma once
#include "ArgumentOutOfRangeException.h"
#include "Collections/Iterators/IRandomAccessIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T>
      class PointerIterator final : public virtual Iterators::IRandomAccessIterator<T>
      {
      public:
        #pragma region Constructors
        PointerIterator(std::add_pointer_t< std::remove_reference_t<T> > begin,
                        std::add_pointer_t< std::remove_reference_t<T> > current,
                        std::add_pointer_t< std::remove_reference_t<T> > end)
          : _begin(begin), _current(current), _end(end)
        {}

        class PointerIterator(const PointerIterator<T>& original)
          : PointerIterator(original._begin, original._current, original._end)
        {
        }

        class PointerIterator(PointerIterator<T>&& old)
          : _begin(old._begin), _current(old._current), _end(old._end)
        {
          old._begin = nullptr;
          old._current = nullptr;
          old._end = nullptr;
        }
        #pragma endregion

        #pragma region IRandomAccessIterator
        virtual void assign(const IIterator<T>& rhs) override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
          {
            _begin = iterator->_begin;
            _current = iterator->_current;
            _end = iterator->_end;
          }

          THROW(Exception, "Not a pointer iterator type")
        }

        virtual PointerIterator<T>& operator++() override
        {
          ++_current;
          return *this;
        }

        virtual PointerIterator<T>& operator++(int) override
        {
          _current++;
          return *this;
        }

        virtual PointerIterator<T>& operator--() override
        {
          --_current;
          return *this;
        }

        virtual PointerIterator<T>& operator--(int) override
        {
          _current--;
          return *this;
        }

        virtual PointerIterator<T>& operator+=(int offset) override
        {
          _current += offset;
          if (_current > _end)
            _current = _end;
          return *this;
        }

        virtual PointerIterator<T>& operator-=(int offset) override
        {
          _current -= offset;
          if (_current < _begin)
            _current = _begin;
          return *this;
        }

        virtual bool operator==(const IInputIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
            return _current == iterator->_current;

          return false;
        }

        virtual std::add_lvalue_reference_t<T> operator*() const override
        {
          return *_current;
        }

        virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const override
        {
          return _current;
        }

        virtual bool operator<(const IRandomAccessIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
            return _current < iterator->_current;

          THROW(Exception, "Not a PointerIterator")
        }

        virtual bool operator<=(const IRandomAccessIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
            return _current <= iterator->_current;

          THROW(Exception, "Not a PointerIterator")
        }

        virtual bool operator>(const IRandomAccessIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
            return _current > iterator->_current;

          THROW(Exception, "Not a PointerIterator")
        }

        virtual bool operator>=(const IRandomAccessIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const PointerIterator*>(&rhs))
            return _current >= iterator->_current;

          THROW(Exception, "Not a PointerIterator")
        }

        virtual std::add_lvalue_reference_t<T> operator[](size_t location) const override
        {
          auto position = _begin + location;
          if (position < _end)
            return *position;

          THROW(ArgumentOutOfRangeException, "location")
        }

        virtual std::unique_ptr< Iterators::IIterator<T> > clone() const override
        {
          return std::make_unique< PointerIterator<T> >(*this);
        }

        virtual std::unique_ptr< IIterator< std::add_const_t<T> > > getConst() const override
        {
          return std::make_unique< PointerIterator< std::add_const_t<T> > >(_begin, _current, _end);
        }

        #pragma region Assignable
        PointerIterator<T>& operator=(const PointerIterator<T>& rhs)
        {
          assign(rhs);
          return *this;
        }
        #pragma endregion
        #pragma endregion
      private:
        #pragma region Variables
        std::add_pointer_t< std::remove_reference_t<T> > _begin;
        std::add_pointer_t< std::remove_reference_t<T> > _current;
        std::add_pointer_t< std::remove_reference_t<T> > _end;
        #pragma endregion
      };
    }
  }
}