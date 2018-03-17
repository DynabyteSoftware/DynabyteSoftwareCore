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

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container>
    class ContainerFilterWrapper
      : public IEnumerable<ContainerFilterWrapper<Container>, FilterEnumerator<Container::iterator>>
    {
    public:
      ContainerFilterWrapper(Container container, iterator::filter_function filterFunction)
        : _container(container), _filterFunction(filterFunction)
      {

      }

      virtual iterator begin() override
      {
        return iterator(_container.begin(), _container.end(), _filterFunction);
      }

      virtual iterator end() override
      {
        return iterator(_container.end(), _container.end(), _filterFunction);
      }
    private:
      Container& _container;
      iterator::filter_function _filterFunction;
    };
  }
}