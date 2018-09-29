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
      #pragma region Destructors
      inline virtual ~IEnumerable() {};
      #pragma endregion

      #pragma region Container
      Enumerator<T> begin() const
      {
        return getEnumerator();
      }

      Enumerator<T> end() const
      {
        return getEnumerator().getEnd();
      }
      #pragma endregion

      #pragma region Querying
      T first() const
      {
        return *getEnumerator();
      }
      #pragma endregion

      #pragma region Enumeration
      virtual Enumerator<T> getEnumerator() const = 0;
      #pragma endregion
    };
  }
}