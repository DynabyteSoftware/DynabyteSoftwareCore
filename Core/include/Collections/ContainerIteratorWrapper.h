/***********************************************************************************************************************
* @file ContainerIteratorWrapper.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerIteratorWrapper definition class
**********************************************************************************************************************/

#pragma once
#include "Collections/Declaration/ContainerIteratorWrapper-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    ContainerIteratorWrapper<IteratorType>::ContainerIteratorWrapper(const IteratorType& begin,
                                                                     const IteratorType& end)
      : _begin(begin), _end(end)
    {
    }

    template<typename IteratorType>
    typename ContainerIteratorWrapper<IteratorType>::iterator ContainerIteratorWrapper<IteratorType>::begin()
    {
      return _begin;
    }

    template<typename IteratorType>
    typename ContainerIteratorWrapper<IteratorType>::iterator ContainerIteratorWrapper<IteratorType>::end()
    {
      return _end;
    }
  }
}