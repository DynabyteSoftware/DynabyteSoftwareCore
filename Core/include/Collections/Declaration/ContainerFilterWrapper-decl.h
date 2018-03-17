/***********************************************************************************************************************
* @file ContainerFilterWrapper-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/14
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerIteratorWrapper declaration class
**********************************************************************************************************************/
#pragma once
#include "Collections/FilterEnumerator.h"
#include "Collections/Declaration/IEnumerable-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container>
    class ContainerFilterWrapper
      : public IEnumerable<ContainerFilterWrapper<Container>, FilterEnumerator<typename Container::iterator>>
    {
    public:
      ContainerFilterWrapper(Container& container, const typename iterator::filter_function& filter);

      virtual iterator begin() override;
      virtual iterator end() override;
    private:
      Container& _container;
      typename iterator::filter_function _filter;
    };
  }
}