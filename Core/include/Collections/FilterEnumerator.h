/*******************************************************************************************************************//**
* @file FilterEnumerator.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's FilterEnumerator class
**********************************************************************************************************************/

#pragma once
#include "IEnumerator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    /**************************************************************************************************************//**
    * @class FilterEnumerator
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps an existing iterator into one that filters through the values it iterates
    * @see ForwardIterator
    * @details
    * Wraps an existing iterator into one that skips over any values that cannot pass a given filter condition
    ******************************************************************************************************************/
    template<typename IteratorType>
    class FilterEnumerator final
      : public ForwardIterator<typename IteratorType::value_type, FilterEnumerator<IteratorType>>
    {
    public:
      #pragma region Type Definitions
      typedef typename IteratorType::value_type value_type;
      typedef typename ForwardIterator<value_type, FilterEnumerator<IteratorType>>::reference reference;
      typedef typename ForwardIterator<value_type, FilterEnumerator<IteratorType>>::pointer pointer;
      typedef std::function<bool(const value_type&)> filter_function;
      #pragma endregion

      #pragma region Constructors
      /**
       * Constructor for a FilterEnumerator object
       *
       * @param begin[in] The beginning of the iteration sequence. If the value it points to does not pass the filter
       *                  condition, then the iterator self-iterates until it finds a value that does, or reaches the
       *                  end position
       * @param end[in] An iterator past the end of the sequence. Required because this iterator must self-advance, and
       *                therefore must known when it has reached the end of the sequence
       * @param filter[in] A function that takes in a constant reference to the value in the container and returns
       *                   true if the value should be returned, false if the value should be skipped
       **/
      FilterEnumerator(const IteratorType& begin, const IteratorType& end, const filter_function& filter)
        : _current(begin), _end(end), _filter(filter)
      {
        if(begin != end && !filter(*begin))
          operator++();
      }
      #pragma endregion

      #pragma region ForwardIterator
      /**
       * Advances this iterator to the next value that passes the filter condition
       * @return A reference to this advanced operator
       **/
      virtual FilterEnumerator& operator++() override
      {
        do
          ++_current;
        while(_current != _end && !_filter(*_current));

        return *this;
      }

      /**
       * Assigns this enumerator to another
       * @param rhs[in] The enumerator to copy into this one
       * @return a reference to this enumerator after it has been assigned the value in rhs 
       **/
      virtual FilterEnumerator& operator=(const FilterEnumerator& rhs) override
      {
        _current = rhs._current;
        _end = rhs._end;
        _filter = rhs._filter;

        return *this;
      }

      /**
       * Dereferences this enumerator
       *
       * @return A reference to the value this enumerator is pointing to
       **/
      virtual reference operator*() const override
      {
        return *_current;
      }

      /**
       * Gets the address of pointed value
       * @return A pointer to the value this enumerator is pointing to
       **/
      virtual pointer operator->() const override
      {
        return _current.operator->();
      }

      /**
       * Determines if this enumerator is pointing to the same object as another
       * @return true if this enumerator points to the same object location as rhs
       * @note will return true even if filter is different, this evaluation is intended to be used to determine
       *       if the location in the sequence is a match only
       **/
      virtual bool operator==(const FilterEnumerator& rhs) const override
      {
        return _current == rhs._current;
      }
      #pragma endregion
    private:
      IteratorType _current;
      IteratorType _end;
      filter_function _filter;
    };
  }
}
