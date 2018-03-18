/***********************************************************************************************************************
* @file IEnumerable-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's IEnumerable declaration class
**********************************************************************************************************************/

#pragma once
#include "Collections/FilterEnumerator.h"
#include "Collections/TransformEnumerator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename> class ContainerIteratorWrapper;
    template<typename> class ContainerFilterWrapper;
    template<typename,typename> class ContainerTransformWrapper;

    /******************************************************************************************************************
    * @class IEnumerable
    * @ingroup DynabyteSoftware::Collections
    * @brief Base class for containers that provide additional features than stl containers
    * @see IEnumerable
    * @details
    * Base class for containers that provides functionality to perform operations based on the entire sequence
    * @note Classes inheriting from IEnumerable are not guaranteed to be thread-safe, that must be handled by the
    *       derived class. Operations such as select and where which return wrappers are never thread-safe
    ******************************************************************************************************************/
    template<typename Container, typename IteratorType>
    class IEnumerable
    {
    public:
      #pragma region Type Definitions
      typedef typename IteratorType::value_type value_type;
      typedef typename IteratorType::reference reference;
      typedef typename std::add_const<reference>::type const_reference;
      typedef IteratorType iterator;
      typedef typename std::add_const<iterator>::type const_iterator;
      typedef typename iterator::difference_type difference_type;
      typedef size_t size_type;
      typedef FilterEnumerator<iterator> filter_iterator;
      #pragma endregion

      #pragma region Destructors
      /**
       * Destructor for IEnumerable
       **/
      inline virtual ~IEnumerable(){};
      #pragma endregion

      #pragma region Pure Virtual Functions
      /**
       * @return iterator to the beginning of the sequence
       **/
      virtual iterator begin() = 0;
      /**
       * @return iterator to the end of the sequence
       **/
      virtual iterator end() = 0;
      #pragma endregion

      #pragma region Functions
      /**
       * Evaluates whether any element exists in the sequence that satisfies a condition
       *
       * @param filter[in] A function that takes in a constant reference to the value in the container and returns
       *                   true if the value should be returned, false if the value should be skipped
       * @return true if any element in the sequence satisfies the condition in the filter
       **/
      bool any(typename const filter_iterator::filter_function& filter);
      /**
       * @return constant iterator to the beginning of the sequence
       **/
      const_iterator cbegin() const;
      /**
       * @return constant iterator past the beginning of the sequence
       **/
      const_iterator cend() const;
      /**
       * @return reference to the first value in the sequence
       **/
      reference front() const;

      /**
       * Returns the values of this container such that they are transformed in the manner according to the transform
       * function provided
       * @param transform The transform function that determines how the values are to be transformed
       * @return A wrapper container that iterates through the contents of this container transforming any values
       *         within in the manner specified by the transform function
       * @note The transformation evaluation does not occur immediately. Instead the container wrapper and iterators
       *       are created such that a lazy evaluation is performed when the wrapper is iterated
       * @note The wrapper returned by this function is valid for as long as the container is valid. It holds a
       *       reference to the container, not a copy, so changes to the container affect the results of the wrapper.
       **/
      template<typename ValueType>
      ContainerTransformWrapper<Container, ValueType>
        select(typename const TransformEnumerator<ValueType, iterator>::transform_function& transform);

      /**
      * Returns only the values of this container that pass the filter function evaluation
      * @param filter The filter function takes in const references to the values in the container and returns true
      *        when the value is to be iterated or false when it is to be skipped
      * @return A wrapper container that iterates through the contents of this container filtering any values
      *         within in the manner specified by the filter function
      * @note The filter evaluation does not occur immediately. Instead the container wrapper and iterators
      *       are created such that a lazy evaluation is performed when the wrapper is iterated
      * @note The wrapper returned by this function is valid for as long as the container is valid. It holds a
      *       reference to the container, not a copy, so changes to the container affect the results of the wrapper.
      **/
      ContainerFilterWrapper<Container> where(typename const filter_iterator::filter_function& filter);
      #pragma endregion
    };
  }
}