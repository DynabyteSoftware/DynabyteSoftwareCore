/***********************************************************************************************************************
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
    template<typename ValueType, typename IteratorType>
    class TransformEnumerator final
      : public ForwardIterator<ValueType, TransformEnumerator<ValueType, IteratorType>>
    {
    public:
      typedef std::function<ValueType(const typename IteratorType::value_type&)> transform_function;

      TransformEnumerator(const IteratorType& begin, const transform_function& transform)
        : _current(begin), _transform(transform)
      {
      }

      #pragma region ForwardIterator
      virtual TransformEnumerator& operator++() override
      {
        ++_current;
        return *this;
      }

      virtual TransformEnumerator& operator=(const TransformEnumerator& rhs) override
      {
        _current = rhs._current;
        _transform = rhs._transform;

        return *this;
      }

      virtual reference operator*() const override
      {
        if constexpr (std::is_reference<ValueType>::value)
          return _transform(*_current);
        
        _value = _transform(*_current);
        return _value;
      }

      virtual pointer operator->() const override
      {
        _value = _transform(*_current);
        return &_value;
      }

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