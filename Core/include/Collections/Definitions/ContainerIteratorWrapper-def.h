#pragma once
#include "Collections/Definitions/IEnumerable-def.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    class ContainerIteratorWrapper : public IEnumerable<IteratorType>
    {
    public:
      ContainerIteratorWrapper(const IteratorType& begin, const IteratorType& end);

      virtual iterator begin() override;
      virtual iterator end() override;
    private:
      IteratorType _begin;
      IteratorType _end;
    };
  }
}