#pragma once
#include "Collections/TemplateDeclarations/IEnumerable-decl.h"
#include "Collections/Wrappers/EnumeratorWrapper.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    #pragma region Container
    template<typename T>
    typename IEnumerable<T>::iterator IEnumerable<T>::begin() const
    {
      return getEnumerator();
    }

    template<typename T>
    typename IEnumerable<T>::const_iterator IEnumerable<T>::cbegin() const
    {
      return begin();
    }

    template<typename T>
    typename IEnumerable<T>::iterator IEnumerable<T>::end() const
    {
      return getEnumerator().getEnd();
    }

    template<typename T>
    typename IEnumerable<T>::const_iterator IEnumerable<T>::cend() const
    {
      return end();
    }
    #pragma endregion

    #pragma region Querying
    template<typename T>
    bool IEnumerable<T>::all(const typename Wrappers::FilterIterator< std::add_const_t<T> >
                                                    ::filter_function& filter) const
    {
      for (auto it = cbegin(); it != cend(); ++it)
        if (!filter(*it))
          return false;

      return true;
    }

    template<typename T>
    bool IEnumerable<T>::any(const typename Wrappers::FilterIterator< std::add_const_t<T> >
                                                    ::filter_function& filter) const
    {
      for (auto it = cbegin(); it != cend(); ++it)
        if (filter(*it))
          return true;

      return false;
    }

    template<typename T>
    T IEnumerable<T>::first() const
    {
      return *cbegin();
    }

    template<typename T>
    Wrappers::EnumeratorWrapper<T> IEnumerable<T>::where(const typename Wrappers::FilterIterator< std::add_const_t<T> >
                                                                                ::filter_function& filter) const
    {
      return make_enumerator(FilterIterator<T>(begin(), filter), FilterIterator<T>(end(), filter));
    }
    #pragma endregion
  }
}