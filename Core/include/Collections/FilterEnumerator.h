#pragma once
#include "IEnumerator.h"
#include <functional>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    class FilterEnumerator final
      : public ForwardIterator<typename IteratorType::value_type, FilterEnumerator<IteratorType>>
    {
    public:
      typedef std::function<bool(const typename value_type&)> filter_function;

      FilterEnumerator(const IteratorType& begin, const IteratorType& end, const filter_function& filter)
        : _current(begin), _end(end), _filter(filter)
      {
        if(begin != end && !filter(*begin))
          operator++();
      }

      #pragma region ForwardIterator
      virtual FilterEnumerator& operator++() override
      {
        do
          ++_current;
        while(_current != _end && !_filter(*_current));

        return *this;
      }

      virtual FilterEnumerator& operator=(const FilterEnumerator& rhs) override
      {
        _current = rhs._current;
        _end = rhs._end;
        _filter = rhs._filter;

        return *this;
      }

      virtual reference operator*() const override
      {
        return *_current;
      }

      virtual pointer operator->() const override
      {
        return _current.operator->();
      }

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