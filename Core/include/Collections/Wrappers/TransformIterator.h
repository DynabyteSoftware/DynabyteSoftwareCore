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
      template<typename T, typename U>
      class TransformIterator final : public Iterators::IForwardIterator<U>
      {
      public:
        #pragma region Transform Function
        typedef std::function<U(std::add_lvalue_reference_t< T > value)> transform_function;
        #pragma endregion

        #pragma region Constructors
        TransformIterator(const Enumerator<T>& enumerator, const transform_function& transformFunction)
          : _enumerator(enumerator), _transformFunction(transformFunction)
        {
        }
        #pragma endregion

        #pragma region IForwardIterator
        virtual TransformIterator<T>& operator++() override
        {
          ++_enumerator;
          return *this;
        }

        virtual TransformIterator<T>& operator++(int) override
        {
          _enumerator++;
          return *this;
        }

        virtual bool operator==(const IInputIterator<U>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const TransformIterator*>(&rhs))
            return _enumerator == iterator->_enumerator;

          return false;
        }

        virtual std::add_lvalue_reference_t<U> operator*() const override
        {
          if constexpr(std::is_reference_v<U> || std::is_pointer_v<U>)
            return _transform_function(*_enumerator);

          _cache = std::make_shared<U>(_transform_function(*_enumerator));
          return *_cache->get();
        }

        virtual std::add_pointer_t< std::remove_reference_t<U> > operator->() const override
        {
          return &operator*();
        }

        virtual void assign(const IIterator<U>& rhs) override
        {
          if (const auto* iterator = dynamic_cast<const TransformIterator<T, U>*>(&rhs))
          {
            _enumerator = iterator->_enumerator;
            _transformFunction = iterator->_transformFunction;
            _cache = iterator->_cache;
          }

          THROW(Exception, "Not a transform iterator type")
        }

        virtual std::unique_ptr< Iterators::IIterator<U> > clone() const override
        {
          return std::make_unique< TransformIterator<T, U> >(*this);
        }

        virtual std::unique_ptr< IIterator< std::add_const_t<U> > > getConst() const override
        {
          return std::make_unique< TransformIterator< std::add_const_t<T>,
                                                      std::add_const_t<U> > >(dynamic_cast<Enumerator<const T>&>(*_enumerator.getConst()),
                                                                              _transformFunction);
        }
        #pragma endregion
      private:
        #pragma region Variables
        Enumerator<T> _enumerator;
        transform_function _transformFunction;
        std::shared_ptr< std::remove_pointer_t<U> > _cache;
        #pragma endregion
      };
    }
  }
}