#pragma once
#include "Collections/Iterators/IForwardIterator.h"
#include "Exception.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class Enumerator final : public virtual Iterators::IForwardIterator<T>
    {
    public:
      #pragma region Constructors
      Enumerator(const Enumerator<T>& original)
        : Enumerator(original._begin, *original._current, original._end)
      {
      }

      Enumerator(Enumerator<T>&& old)
        : _begin(std::move(old._begin)), _end(std::move(old._end)), _current(std::move(old._current))
      {
      }
      #pragma endregion

      #pragma region Observers
      const Enumerator<T> getEnd() const
      {
        return Enumerator<T>(_begin, *_end, _end);
      }
      #pragma endregion

      #pragma region IForwardIterator
      virtual void assign(const Iterators::IIterator<T>& rhs) override
      {
        if(const auto* iterator = dynamic_cast<const Enumerator<T>*>(&rhs))
        {
          _begin = iterator->_begin;
          _end = iterator->_end;
          *_current = *iterator->_current;
        }
        else
          THROW(Exception, "iterator not an enumerator")
      }

      virtual std::unique_ptr< IIterator< std::add_const_t<T> > > getConst() const override
      {
        return std::make_unique< Enumerator< std::add_const_t<T> > >(this->operator Enumerator<std::add_const_t<T>>());
      }

      operator Enumerator< std::add_const_t<T> >() const
      {
        struct IteratorCast
        {
          typedef std::add_const_t<T> ConstT;
          typedef Iterators::IForwardIterator< ConstT > ConstIterator;
          
          static std::shared_ptr< ConstIterator > cast(const Iterators::IForwardIterator< T >& iterator)
          {
            return std::shared_ptr< ConstIterator >(dynamic_cast<ConstIterator*>(iterator.getConst().release()));
          }
        };
        
        return Enumerator< std::add_const_t<T> >(IteratorCast::cast(*_begin), *IteratorCast::cast(*_current),
                                                 IteratorCast::cast(*_end));
      }

      Enumerator<T>& operator++() override
      {
        if(*_current == *_end)
          THROW(Exception, "Attempted to advance past end of container")

        _current->operator++();
        return *this;
      }

      Enumerator<T>& operator++(int value) override
      {
        if(*_current == *_end)
          THROW(Exception, "Attempted to advance past end of container")

        _current->operator++(value);
        return *this;
      }

      #pragma region Equatable
      virtual bool operator==(const IInputIterator<T>& rhs) const override
      {
        if(const auto* iterator = dynamic_cast<const Enumerator<T>*>(&rhs))
        {
          return *iterator->_current == *_current;
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

      #pragma region Cloneable
      virtual std::unique_ptr< Iterators::IIterator<T> > clone() const override
      {
        return std::make_unique< Enumerator<T> >(*this);
      }
      #pragma endregion
      #pragma endregion

      #pragma region Observers
      template<typename IteratorType>
      IteratorType& castCurrent()
      {
        return dynamic_cast<IteratorType&>(*_current);
      }
      #pragma endregion

      #pragma region Operators
      Enumerator<T>& operator=(const Enumerator<T>& rhs)
      {
        assign(rhs);
        return *this;
      }
      #pragma endregion
    private:
      #pragma region Variables
      std::shared_ptr< const Iterators::IForwardIterator<T> > _begin;
      std::shared_ptr< const Iterators::IForwardIterator<T> > _end;
      std::unique_ptr< Iterators::IForwardIterator<T> > _current;
      #pragma endregion

      #pragma region Constructors
      #pragma warning(push)
      #pragma warning(disable:4436)
      Enumerator(const std::shared_ptr< const Iterators::IForwardIterator<T> >& begin,
                 const Iterators::IForwardIterator<T>& current,
                 const std::shared_ptr< const Iterators::IForwardIterator<T> >& end)
        : _begin(begin), _end(end),
          _current(dynamic_cast< Iterators::IForwardIterator<T>* >(current.clone().release()))
      {
      }
      #pragma warning(pop)
      #pragma endregion

      #pragma region Friend Declarations
      template<typename U=T, template<typename> typename IteratorType>
      friend Enumerator<U> make_enumerator(const IteratorType<U>& begin, const IteratorType<U>& end);
      template<typename U=T, typename V, template<typename,typename> typename IteratorType>
      friend Enumerator<U> make_enumerator(const IteratorType<U, V>& begin, const IteratorType<U, V>& end);
      template<typename> friend class Enumerator;
      #pragma endregion
    };

    template<typename T, template<typename> typename IteratorType>
    Enumerator<T> make_enumerator(const IteratorType<T>& begin, const IteratorType<T>& end)
    {
      return Enumerator<T>(std::make_shared< IteratorType<T> >(begin), begin,
                           std::make_shared< IteratorType<T> >(end));
    }

    template<typename T, typename U, template<typename,typename> typename IteratorType>
    Enumerator<T> make_enumerator(const IteratorType<T, U>& begin, const IteratorType<T, U>& end)
    {
      return Enumerator<T>(std::make_shared< IteratorType<T, U> >(begin), begin,
                           std::make_shared< IteratorType<T, U> >(end));
    }
  }
}