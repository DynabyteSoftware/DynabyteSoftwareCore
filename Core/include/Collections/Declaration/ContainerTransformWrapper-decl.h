/***********************************************************************************************************************
* @file ContainerTransformWrapper-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/17
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerIteratorWrapper declaration class
**********************************************************************************************************************/
#pragma once
#include "Collections/TransformEnumerator.h"
#include "Collections/Declaration/IEnumerable-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename Container, typename ValueType>
    class ContainerTransformWrapper
      : public IEnumerable<ContainerTransformWrapper<Container, ValueType>,
                           TransformEnumerator<ValueType, typename Container::iterator>>
    {
    public:
      ContainerTransformWrapper(Container& container, const typename iterator::transform_function& filter);

      virtual iterator begin() override;
      virtual iterator end() override;
    private:
      Container& _container;
      typename iterator::transform_function _transform;
    };
  }
}