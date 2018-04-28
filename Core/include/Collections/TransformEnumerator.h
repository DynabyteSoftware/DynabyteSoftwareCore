/*******************************************************************************************************************//**
* @file TransformEnumerator.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's TransformEnumerator class
**********************************************************************************************************************/

#pragma once
#include "IEnumerator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    /**************************************************************************************************************//**
    * @class TransformEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps an existing iterator into one that performs a transformation on the values it iterates through
    * @see ForwardIterator
    * @details
    * Wraps an existing iterator into one that transforms the values it iterates through by going through the provided
    * transform function
    ******************************************************************************************************************/
    template<typename ValueType, typename IteratorType>
    class TransformEnumerator final
      : public ForwardIterator<ValueType, TransformEnumerator<ValueType, IteratorType>>
    {
    public:
      #pragma region Type Definition
      typedef std::function<ValueType(const typename IteratorType::value_type&)> transform_function;
      typedef typename ForwardIterator<ValueType, TransformEnumerator<ValueType, IteratorType>>::reference reference;
      typedef typename ForwardIterator<ValueType, TransformEnumerator<ValueType, IteratorType>>::pointer pointer;
      #pragma endregion

      #pragma region Constructors and Destructors
      /**
       * Constructor for a TransformEnumerator
       *
       * @param begin[in] Iterator to begin iterating from
       * @param transform[in] Transform function to pass through the value being currently pointed to
       **/
      TransformEnumerator(const IteratorType& begin, const transform_function& transform)
        : _current(begin), _transform(transform)
      {
      }
      #pragma endregion

      #pragma region ForwardIterator
      /**
       * Advances the current iterator
       * @return A reference to this iterator after it's been advanced
       **/
      virtual TransformEnumerator& operator++() override
      {
        ++_current;
        return *this;
      }

      /**
       * Assignment operator
       * @param rhs[in] The iterator to copy
       * @return A reference to this iterator after it copied the values from rhs
       **/
      virtual TransformEnumerator& operator=(const TransformEnumerator& rhs) override
      {
        _current = rhs._current;
        _transform = rhs._transform;

        return *this;
      }

      /**
       * Dereferencing Operator
       * @return The transformed value this iterator is pointing to
       * @note The reference is only valid until while this iterator is valid and not advanced
       **/
      virtual reference operator*() const override
      {
        if constexpr (std::is_reference<ValueType>::value)
          return _transform(*_current);
        
        _value = _transform(*_current);
        return _value;
      }

      /**
       * @return A pointer to the transformed value this iterator is point to
       * @note The pointer is only valid while this iterator is valid and not advanced
       **/
      virtual pointer operator->() const override
      {
        if constexpr (std::is_reference<ValueType>::value)
          return &_transform(*_current);

        _value = _transform(*_current);
        return &_value;
      }

      /**
       * EqualityComparison Operator
       * @param rhs[in] Another Transform iterator to compare to
       * @return true if rhs points to the same location in the sequence as this iterator
       * @note will return true even if there are different transform functions. It is meant to determine only if the
       *       iterators are pointing to the same location in the sequence
       **/
      virtual bool operator==(const TransformEnumerator& rhs) const override
      {
        return _current == rhs._current;
      }
      #pragma endregion
    private:
      IteratorType _current;
      transform_function _transform;
      mutable typename std::remove_const<typename std::remove_reference<ValueType>::type>::type _value;
    };
  }
}
