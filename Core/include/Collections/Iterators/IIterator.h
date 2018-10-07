#pragma once
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IIterator
      {
      public:
        #pragma region Destructible
        inline virtual ~IIterator() {};
        #pragma endregion

        #pragma region Copy-Assignable
        IIterator& operator=(const IIterator<T>& rhs)
        {
          assign(rhs);
          return *this;
        }
        #pragma endregion

        #pragma region Incrementable
        virtual IIterator<T>& operator++() = 0;
        virtual IIterator<T>& operator++(int) = 0;
        #pragma endregion

        #pragma region Equatable
        virtual bool operator==(const IIterator<T>& rhs) const = 0;
        inline bool operator!=(const IIterator<T>& rhs) const { return !operator==(rhs); }
        #pragma endregion

        #pragma region R-Value Dereferenceable
        virtual std::add_lvalue_reference_t<T> operator*() const = 0;
        virtual std::add_pointer_t< std::remove_reference_t<T> > operator->() const = 0;
        #pragma endregion

        #pragma region Cloneable
        virtual std::unique_ptr< IIterator<T> > clone() const = 0;        
        virtual std::unique_ptr< IIterator< std::add_const_t<T> > > getConst() const = 0;
        #pragma endregion
      protected:
        #pragma region Copy-Assignable
        virtual void assign(const IIterator<T>& rhs) = 0;
        #pragma endregion
      };
    }
  }
}