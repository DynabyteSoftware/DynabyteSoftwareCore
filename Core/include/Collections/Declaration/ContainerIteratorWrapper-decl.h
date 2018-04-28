/*******************************************************************************************************************//**
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
    /**************************************************************************************************************//**
    * @class ContainerIteratorWrapper
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps existing iterators into an IEnumerable
    * @see IEnumerable
    * @details
    * Wraps existing iterators between a beginning and end point into an IEnumerable container
    ******************************************************************************************************************/
    template<typename IteratorType>
    class ContainerIteratorWrapper : public IEnumerable<ContainerIteratorWrapper<IteratorType>, IteratorType>
    {
    public:
      typedef typename IEnumerable<ContainerIteratorWrapper<IteratorType>, IteratorType>::iterator iterator;
      
      /**
       * Constructor for a ContainerIteratorWrapper object
       *
       * @param begin[in] iterator to the beginning of a sequence
       * @param end[in] iterator past the end of a sequence
       **/
      ContainerIteratorWrapper(const IteratorType& begin, const IteratorType& end);

      /**
       * @return iterator to the beginning of the container
       **/
      virtual iterator begin() override;
      /**
       * @return iterator past the end of the container
       **/
      virtual iterator end() override;
    private:
      IteratorType _begin;
      IteratorType _end;
    };
  }
}
