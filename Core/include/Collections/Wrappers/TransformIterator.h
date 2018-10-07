#pragma once
#include "Collections/Enumerator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T, typename U>
      class TransformIterator final : public Iterators::IIterator<U>
      {
      public:
        #pragma region Transform Function
        typedef std::function<U(std::add_lvalue_reference_t< T >)> transform_function;
        typedef std::function < std::add_const_t<U>(std::add_lvalue_reference_t< std::add_const_t<T> >)>
          const_transform_function;
        #pragma endregion

        #pragma region Constructors
        template< typename V = T,
                  typename = typename std::enable_if_t< !std::is_same_v<transform_function,
                                                                        const_transform_function> > >
        TransformIterator(const Enumerator<T>& enumerator, const transform_function& transformFunction)
          : _enumerator(enumerator), _transformFunction(transformFunction)
        {
        }

        TransformIterator(const Enumerator<T>& enumerator, const const_transform_function& transformFunction)
          : _enumerator(enumerator), _constTransformFunction(transformFunction)
        {
        }
        #pragma endregion

        #pragma region IIterator
        virtual TransformIterator<T, U>& operator++() override
        {
          ++_enumerator;
          return *this;
        }

        virtual TransformIterator<T, U>& operator++(int) override
        {
          _enumerator++;
          return *this;
        }

        virtual bool operator==(const Iterators::IIterator<U>& rhs) const override
        {
          if (const auto* iterator = dynamic_cast<const TransformIterator<T,U>*>(&rhs))
            return _enumerator == iterator->_enumerator;

          return false;
        }

        virtual std::add_lvalue_reference_t<U> operator*() const override
        {
          if constexpr(std::is_reference_v<U> || std::is_pointer_v<U>)
            return _transformFunction(*_enumerator);

          _cache = std::make_shared<U>(_transformFunction(*_enumerator));

          return *_cache.get();
        }

        virtual std::add_pointer_t< std::remove_reference_t<U> > operator->() const override
        {
          return &operator*();
        }

        virtual void assign(const Iterators::IIterator<U>& rhs) override
        {
          if (const auto* iterator = dynamic_cast<const TransformIterator<T, U>*>(&rhs))
          {
            _enumerator = iterator->_enumerator;
            _transformFunction = iterator->_transformFunction;
            _constTransformFunction = iterator->_constTransformFunction;
            _cache = iterator->_cache;
          }

          THROW(Exception, "Not a transform iterator type")
        }

        virtual std::unique_ptr< Iterators::IIterator<U> > clone() const override
        {
          return std::make_unique< TransformIterator<T, U> >(*this);
        }

        virtual std::unique_ptr< Iterators::IIterator< std::add_const_t<U> > > getConst() const override
        {
          return std::make_unique< TransformIterator< std::add_const_t<T>,
                                                      std::add_const_t<U> > >
            (dynamic_cast<Enumerator<const T>&>(*_enumerator.getConst()), _constTransformFunction);
        }
        #pragma endregion
      private:
        #pragma region Variables
        Enumerator<T> _enumerator;
        transform_function _transformFunction;
        const_transform_function _constTransformFunction;
        mutable std::shared_ptr< std::remove_pointer_t<U> > _cache;
        #pragma endregion
      };
    }
  }
}