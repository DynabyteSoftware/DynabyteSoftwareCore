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
    /******************************************************************************************************************
    * @class ContainerTransformWrapper
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps an existing container into one that transforms the contents into a different type
    * @see IEnumerable
    * @see TransformEnumerator
    * @details
    * Wraps an existing container into one that uses transform iterators to turn the value into container into a 
    * different value based on a given function
    ******************************************************************************************************************/
    template<typename Container, typename ValueType>
    class ContainerTransformWrapper
      : public IEnumerable<ContainerTransformWrapper<Container, ValueType>,
                           TransformEnumerator<ValueType, typename Container::iterator>>
    {
    public:
      /**
       * Constructor for a ContainerTransformWrapper object
       *
       * @param container[in,out] The container being wrapped
       * @param transform[in] The transform function to change the values in the container to the value returned by
       *                      this wrapper
       **/
      ContainerTransformWrapper(Container& container, const typename iterator::transform_function& filter);

      /**
       * @return iterator to the beginning of the container
       **/
      virtual iterator begin() override;
      /**
       * @return iterator past the end of the container
       **/
      virtual iterator end() override;
    private:
      Container& _container;
      typename iterator::transform_function _transform;
    };
  }
}