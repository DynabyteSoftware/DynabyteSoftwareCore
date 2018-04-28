/*******************************************************************************************************************//**
* @file ContainerFilterWrapper.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/17
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerFilterWrapper definition class
**********************************************************************************************************************/
#pragma once
#include "Collections/Declaration/ContainerFilterWrapper-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container>
    ContainerFilterWrapper<Container>
      ::ContainerFilterWrapper(Container& container, const typename iterator::filter_function& filter)
      : _container(container), _filter(filter)
    {
    }

    template<typename Container>
    typename ContainerFilterWrapper<Container>::iterator ContainerFilterWrapper<Container>::begin()
    {
      return iterator(_container.begin(), _container.end(), _filter);
    }

    template<typename Container>
    typename ContainerFilterWrapper<Container>::iterator ContainerFilterWrapper<Container>::end()
    {
      return iterator(_container.end(), _container.end(), _filter);
    }
  }
}
