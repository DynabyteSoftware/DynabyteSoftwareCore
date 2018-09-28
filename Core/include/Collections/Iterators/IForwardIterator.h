#pragma once
#include "Collections/Iterators/IInputIterator.h"
#include "Collections/Iterators/IOutputIterator.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Iterators
    {
      template<typename T>
      class IForwardIterator
        : public virtual IInputIterator<T>
      {

      };
    }
  }
}