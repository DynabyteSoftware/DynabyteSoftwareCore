#pragma once
#include "Collections/Enumerator.h"
#include "Collections/Wrappers/FilterIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename> class EnumeratorWrapper;
    }

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
      iterator begin() const;
      const_iterator cbegin() const;
      iterator end() const;
      const_iterator cend() const;
      #pragma endregion

      #pragma region Querying
      bool all(const typename Wrappers::FilterIterator< std::add_const_t<T> >::filter_function& filter) const;
      bool any(const typename Wrappers::FilterIterator< std::add_const_t<T> >::filter_function& filter) const;
      T first() const;
      Wrappers::EnumeratorWrapper<T> where(const typename Wrappers::FilterIterator< std::add_const_t<T> >
                                                                  ::filter_function& filter) const;
      #pragma endregion

      #pragma region Enumeration
      virtual Enumerator<T> getEnumerator() const = 0;
      #pragma endregion
    };
  }
}