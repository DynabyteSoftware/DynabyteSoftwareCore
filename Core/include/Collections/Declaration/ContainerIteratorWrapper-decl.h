/***********************************************************************************************************************
* @file ContainerIteratorWrapper-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerIteratorWrapper declaration class
**********************************************************************************************************************/

#pragma once
#include "Collections/Declaration/IEnumerable-decl.h"

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