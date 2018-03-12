/***********************************************************************************************************************
* @file IEnumerator.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's IEnumerator class
**********************************************************************************************************************/

#pragma once
#include <iterator>
#include <type_traits>

namespace DynabyteSoftware
{
  namespace Collections
  {
    class IEnumerator
    {
    public:
      typedef std::ptrdiff_t difference_type;

      inline virtual ~IEnumerator(){};

      virtual IEnumerator& operator++() = 0;
    };


    template<typename DerivedIterator>
    class Iterator : public virtual IEnumerator
    {
    public:
      DerivedIterator operator++(int)
      {
        DerivedIterator iterator(*this);
        return std::move(++iterator);
      }

      virtual DerivedIterator& operator=(const DerivedIterator& original) = 0;
    };

    template<typename ValueType>
    class IValueEnumerator : public virtual IEnumerator
    {
    public:
      typedef ValueType value_type;
      typedef typename std::add_pointer<value_type>::type pointer;
      typedef typename std::add_lvalue_reference<value_type>::type reference;
    };

    template<typename ValueType>
    class InputEnumerator : public virtual IValueEnumerator<ValueType>
    {
    public:
      typedef std::input_iterator_tag iterator_category;

      virtual typename reference operator*() const = 0;
      virtual typename pointer operator->() const = 0;
    };

    template<typename ValueType, typename DerivedIterator>
    class InputIterator : public virtual Iterator<DerivedIterator>, public virtual InputEnumerator<ValueType>
    {
    public:
      virtual bool operator==(const DerivedIterator& rhs) const = 0;

      bool operator!=(const DerivedIterator& rhs) const
      {
        return !operator==(rhs);
      }
    };

    template<typename ValueType>
    class OutputEnumerator : public virtual IValueEnumerator<ValueType>
    {
    public:
      typedef std::output_iterator_tag iterator_category;

      virtual reference operator*() const = 0;
      virtual pointer operator->() const = 0;
    };

    template<typename ValueType, typename DerivedIterator>
    class OutputIterator : public virtual Iterator<DerivedIterator>, public virtual OutputEnumerator<ValueType>
    {
    };

    template<typename ValueType>
    class ForwardEnumerator : public virtual OutputEnumerator<ValueType>, public virtual InputEnumerator<ValueType>
    {
      typedef std::forward_iterator_tag iterator_category;
    };

    template<typename ValueType, typename DerivedIterator>
    class ForwardIterator
      : public virtual OutputIterator<ValueType, DerivedIterator>,
      public virtual InputIterator<ValueType, DerivedIterator>, public virtual ForwardEnumerator<ValueType>
    {
    };
  }
}