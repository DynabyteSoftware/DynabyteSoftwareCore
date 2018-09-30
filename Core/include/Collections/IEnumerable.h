#pragma once
#include "Collections/Enumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class IEnumerable
    {
    public:
      #pragma region Type Definitions
      typedef Enumerator<T> iterator;
      typedef Enumerator< std::add_const_t<T> > const_iterator;
      #pragma endregion

      #pragma region Destructors
      inline virtual ~IEnumerable() {};
      #pragma endregion

      #pragma region Container
      iterator begin() const
      {
        return getEnumerator();
      }

      const_iterator cbegin() const
      {
        return begin();
      }

      iterator end() const
      {
        return getEnumerator().getEnd();
      }

      const_iterator cend() const
      {
        return end();
      }
      #pragma endregion

      #pragma region Querying
      T first() const
      {
        return *cbegin();
      }
      #pragma endregion

      #pragma region Enumeration
      virtual Enumerator<T> getEnumerator() const = 0;
      #pragma endregion
    };
  }
}