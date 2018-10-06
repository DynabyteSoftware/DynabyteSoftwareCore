#pragma once
#include "Collections/Enumerator.h"
#include "Collections/Iterators/IForwardIterator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T>
      class FilterIterator final : public Iterators::IForwardIterator<T>
      {
      public:
        #pragma region Transform Function
        typedef std::function<bool(std::add_lvalue_reference_t< std::add_const_t<T> > value)> filter_function;
        #pragma endregion

        #pragma region Constructors
        FilterIterator(const Enumerator<T>& enumerator, const filter_function& filterFunction)
          : _enumerator(enumerator), _filterFunction(filterFunction)
        {
          if (!_filterFunction(*_enumerator))
            operator++();
        }

        /*FilterIterator(const FilterIterator& original)
          : _enumerator(original._enumerator), _filterFunction(original._filterFunction)
        {
        }

        FilterIterator(FilterIterator&& old)
          : _enumerator(std::move(old._enumerator)), _filterFunction(std::move(old._filterFunction))
        {
        }*/
        #pragma endregion

        #pragma region IForwardIterator
        virtual FilterIterator<T>& operator++() override
        {
          while(!(_filterFunction(*_enumerator) || _enumerator == _enumerator.getEnd()))
            ++_enumerator;
          return *this;
        }

        virtual FilterIterator<T>& operator++(int) override
        {
          while(!(_filterFunction(*_enumerator) || _enumerator == _enumerator.getEnd()))
            _enumerator++;
          return *this;
        }

        virtual bool operator==(const IInputIterator<T>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const FilterIterator*>(&rhs))
            return _enumerator == iterator->_enumerator;

          return false;
        }

        virtual std::add_lvalue_reference_t<T> operator*() const override
        {
          return *_enumerator;
        }

        virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const override
        {
          return _enumerator.operator->();
        }

        virtual void assign(const IIterator<T>& rhs) override
        {
          if (const auto* iterator = dynamic_cast<const FilterIterator<T>*>(&rhs))
          {
            _enumerator = iterator->_enumerator;
            _filterFunction = iterator->_filterFunction;
          }

          THROW(Exception, "Not a filter iterator type")
        }

        virtual std::unique_ptr< Iterators::IIterator<T> > clone() const override
        {
          return std::make_unique< FilterIterator<T> >(*this);
        }

        virtual std::unique_ptr< IIterator< std::add_const_t<T> > > getConst() const override
        {
          return std::make_unique< FilterIterator< std::add_const_t<T> > >(dynamic_cast<Enumerator<const T>&>(*_enumerator.getConst()),
                                                                           _filterFunction);
        }
        #pragma endregion
      private:
        #pragma region Variables
        Enumerator<T> _enumerator;
        filter_function _filterFunction;
        #pragma endregion
      };
    }
  }
}