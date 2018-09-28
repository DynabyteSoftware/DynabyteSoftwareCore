#pragma once
#include "Collections/Iterators/IIterator.h"
#include "Exception.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    class Enumerator final
    {
    public:
      #pragma region Constructors and Destructors
      Enumerator(const IteratorType& current, const IteratorType& end)
        : _begin(current), _end(end), _current(dynamic_cast<IteratorType*>(current.clone().release()))
      {
      }

      Enumerator(const Enumerator<IteratorType>& original)
        : Enumerator(original._begin, *original._current, original._end)
      {
      }

      Enumerator(Enumerator<IteratorType>&& old)
        : _begin(std::move(old._begin)), _end(std::move(old._end)), _current(std::move(old._current))
      {
      }
      #pragma endregion

      #pragma region Operators
      Enumerator<IteratorType>& operator=(const Enumerator<IteratorType>& rhs)
      {
        _begin = rhs._begin;
        _end = rhs._end;
        _current = dynamic_cast<IteratorType*>(enumerator->_current.clone().release());
        return *this;
      }

      const IteratorType& begin()
      {
        return _begin;
      }

      const IteratorType& end()
      {
        return _end;
      }

      operator IteratorType&()
      {
        return *_current;
      }
      #pragma endregion
    protected:
      #pragma region Variables
      std::reference_wrapper<const IteratorType> _begin;
      std::reference_wrapper<const IteratorType> _end;
      std::unique_ptr<IteratorType> _current;
      #pragma endregion
    };
  }
}