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
    #pragma region IEnumerator
    /******************************************************************************************************************
    * @class IEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence
    * @details
    * This base class requires a derived class to satisfy the condition that it can be advanced
    ******************************************************************************************************************/
    class IEnumerator
    {
    public:
      typedef std::ptrdiff_t difference_type;

      /**
       * Destructor for IEnumerator
       **/
      inline virtual ~IEnumerator(){};

      /**
       * Advances the IEnumerator
       * @return A reference to this enumerator after it has been advanced
       **/
      virtual IEnumerator& operator++() = 0;
    };
    #pragma endregion

    #pragma region Iterator
    /******************************************************************************************************************
    * @class Iterator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class to help iterators iterate through a sequence
    * @see IEnumerator
    * @details
    * This base class provides functionality for postincrementation of iterators and requires that any iterators that
    * derive from this are copy-assignable, fulfilling the basic requirements of a C++ iterator
    ******************************************************************************************************************/
    template<typename DerivedIterator>
    class Iterator : public virtual IEnumerator
    {
    public:
      /**
       * Post-increments the iterator
       * @return an iterator that points to the next value in the sequence as this one
       **/
      DerivedIterator operator++(int)
      {
        DerivedIterator iterator(*this);
        return std::move(++iterator);
      }

      /**
       * Copies another iterator of the same type and assigns its value to this one
       * @return A reference to this iterator after it has been assigned the value of the original
       **/
      virtual DerivedIterator& operator=(const DerivedIterator& original) = 0;
    };
    #pragma endregion

    #pragma region IValueEnumerator
    /******************************************************************************************************************
    * @class IValueEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence of a particular value type
    * @see IEnumerator
    * @details
    * This base class sets up required typedefs so that anyone inheriting from it will shown results when queried by 
    * std::iterator_traits
    ******************************************************************************************************************/
    template<typename ValueType>
    class IValueEnumerator : public virtual IEnumerator
    {
    public:
      typedef ValueType value_type;
      typedef typename std::add_pointer<value_type>::type pointer;
      typedef typename std::add_lvalue_reference<value_type>::type reference;
    };
    #pragma endregion

    #pragma region InputEnumerator
    /******************************************************************************************************************
    * @class InputEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence and read values from it
    * @see IValueEnumerator
    * @details
    * This base class requires a derived class to satisfy the condition that it can be dereferenced and a pointer to
    * the value can be retrieved
    ******************************************************************************************************************/
    template<typename ValueType>
    class InputEnumerator : public virtual IValueEnumerator<ValueType>
    {
    public:
      typedef std::input_iterator_tag iterator_category;

      /**
       * Dereferences the iterator
       * @return Reference to the value this enumerator is pointing to
       **/
      virtual typename reference operator*() const = 0;
      /**
       * Retrieves address of the pointed value
       * @return Pointer to the value this enumerator is pointing to
       **/
      virtual typename pointer operator->() const = 0;
    };
    #pragma endregion

    #pragma region InputIterator
    /******************************************************************************************************************
    * @class InputIterator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence and read values from it
    * @see Iterator
    * @see InputEnumerator
    * @details
    * This base class requires a derived class to satisfy the EqualityComparable condition and the ability to
    * be dereferenced, satisfying all the condiitons for an InputIterator
    ******************************************************************************************************************/
    template<typename ValueType, typename DerivedIterator>
    class InputIterator : public virtual Iterator<DerivedIterator>, public virtual InputEnumerator<ValueType>
    {
    public:
      /**
       * Compares iterators of the same type and verifies they are pointing to the same location in the sequence
       * @param rhs[in] An iterator of the same type as the derived type from this to compare
       * @return true if both iterators point to the same location in the sequence
       **/
      virtual bool operator==(const DerivedIterator& rhs) const = 0;

      /**
       * Compares iterators of the same type and checks if they are pointing to the same location in the sequence
       * @param rhs[in] An iterator of the same type as the derived type from this to compare
       * @return true if iterators are not pointing to the same lcoation in the sequence
       **/
      bool operator!=(const DerivedIterator& rhs) const
      {
        return !operator==(rhs);
      }
    };
    #pragma endregion

    #pragma region OutputEnumerator
    /******************************************************************************************************************
    * @class OutputEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence and write values to it
    * @see IValueEnumerator
    * @details
    * This base class requires a derived class to satisfy the condition that it can be dereferenced and a pointer to
    * the value can be written to that location
    ******************************************************************************************************************/
    template<typename ValueType>
    class OutputEnumerator : public virtual IValueEnumerator<ValueType>
    {
    public:
      typedef std::output_iterator_tag iterator_category;

      /**
       * Dereferences the iterator
       * @return A modifiable reference to the value this iterator is pointing to
       **/
      virtual reference operator*() const = 0;
      /**
       * Retrieves address of pointed value
       * @return Pointer to the modifiable value this iterator is pointing to
       **/
      virtual pointer operator->() const = 0;
    };
    #pragma endregion

    #pragma region OutputIterator
    /******************************************************************************************************************
    * @class OutputIterator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can iterator through a sequence and write values to it
    * @see Iterator
    * @see OutputEnumerator
    * @details
    * This base class helps a derived class to satisfy the condition that it can be dereferenced and a pointer to
    * the value can be written to that location, satisfying all the conditions of a c++ Output Iterator
    ******************************************************************************************************************/
    template<typename ValueType, typename DerivedIterator>
    class OutputIterator : public virtual Iterator<DerivedIterator>, public virtual OutputEnumerator<ValueType>
    {
    };
    #pragma endregion

    #pragma region ForwardEnumerator
    /******************************************************************************************************************
    * @class ForwardEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can enumerate through a sequence and write values to it
    * @see OutputEnumerator
    * @see InputEnumerator
    * @details
    * This base class requires a derived class to satisfy the condition that it can be dereferenced and a pointer to
    * the value can be written to that location
    ******************************************************************************************************************/
    template<typename ValueType>
    class ForwardEnumerator : public virtual OutputEnumerator<ValueType>, public virtual InputEnumerator<ValueType>
    {
      typedef std::forward_iterator_tag iterator_category;
    };
    #pragma endregion

    #pragma region ForwardIterator
    /******************************************************************************************************************
    * @class ForwardIterator
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for objects that can iterate through a sequence and write values to it
    * @see InputIterator
    * @see ForwardEnumerator
    * @details
    * This base class requires a derived class to satisfy the conditions for both an Input and Output iterator,
    * satisfying the condition for a C++ ForwardIterator
    ******************************************************************************************************************/
    template<typename ValueType, typename DerivedIterator>
    class ForwardIterator
      : public virtual OutputIterator<ValueType, DerivedIterator>,
      public virtual InputIterator<ValueType, DerivedIterator>, public virtual ForwardEnumerator<ValueType>
    {
    };
    #pragma endregion
  }
}