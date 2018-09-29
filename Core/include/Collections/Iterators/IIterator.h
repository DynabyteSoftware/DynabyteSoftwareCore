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
        virtual void assign(const IIterator<T>& rhs) = 0;

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

        #pragma region Cloneable
        virtual std::unique_ptr< IIterator<T> > clone() const = 0;
        #pragma endregion
      };
    }
  }
}